/*
 ===============================================================================
 
 Ebu128LoudnessMeter.cpp
 
 
 This file is part of the LUFS Meter audio measurement plugin.
 Copyright 2011-12 by Klangfreund, Samuel Gaehwiler.
 
 -------------------------------------------------------------------------------
 
 The LUFS Meter can be redistributed and/or modified under the terms of the GNU 
 General Public License Version 2, as published by the Free Software Foundation.
 A copy of the license is included with these source files. It can also be found
 at www.gnu.org/licenses.
 
 The LUFS Meter is distributed WITHOUT ANY WARRANTY.
 See the GNU General Public License for more details.
 
 -------------------------------------------------------------------------------
 
 To release a closed-source product which uses the LUFS Meter or parts of it,
 a commercial license is available. Visit www.klangfreund.com/lufsmeter for more
 information.
 
 ===============================================================================
 */


#include "Ebu128LoudnessMeter.h"

// constants initialisation
const double Ebu128LoudnessMeter::absoluteThreshold = -70.0;
const float Ebu128LoudnessMeter::minimalReturnValue = -300.0f;


Ebu128LoudnessMeter::Ebu128LoudnessMeter()
    : bufferForMeasurement(2, 2048), // Initialise the buffer with some common values.
    // Also initialise the two filters with the coefficients for a sample
    // rate of 44100 Hz. These values are given in the ITU-R BS.1770-2.
    preFilter(1.53512485958697,  // b0
              -2.69169618940638, // b1
              1.19839281085285,  // b2
              -1.69065929318241, // a1
              0.73248077421585), // a2
    revisedLowFrequencyBCurveFilter(1.0,               // b0
                                    -2.0,              // b1
                                    1.0,               // b2
                                    -1.99004745483398, // a1
                                    0.99007225036621), // a2
    // Specifications for the histogram.
    // You might want to change them to e.g. achieve a higher resolution.
    lowestBlockLoudnessToConsider(-80.0), // LUFS
    highestBlockLoudnessToConsider(10.0), // LUFS
    histogramLoudnessStepSize(0.1), // LU
    histogramWeightedSumStepFactor(pow(10.0, histogramLoudnessStepSize/10.0)),
    // Memory allocation for the histogram
    histogramOfBlockLoudness(ceil((highestBlockLoudnessToConsider-lowestBlockLoudnessToConsider)/histogramLoudnessStepSize), 0)
{
    
    
    // If this class is used wrong and processBlock
    // is called before prepareToPlay, divisions by zero
    // might occure. E.g. if numberOfSamplesInAllBins = 0.
    
    // To prevent this, prepareToPlay is called here with
    // some arbitrary arguments.
    prepareToPlay(44100.0, 2, 512, 20);
}

Ebu128LoudnessMeter::~Ebu128LoudnessMeter()
{
}

void Ebu128LoudnessMeter::prepareToPlay (double sampleRate, 
                                         int numberOfInputChannels,
                                         int estimatedSamplesPerBlock, 
                                         int expectedRequestRate)
{
    // Resize the buffer.
    bufferForMeasurement.setSize(numberOfInputChannels, estimatedSamplesPerBlock);
    
    // Set up the two filters for the K-Filtering.
    preFilter.prepareToPlay(sampleRate, numberOfInputChannels);
    revisedLowFrequencyBCurveFilter.prepareToPlay(sampleRate, numberOfInputChannels);
    
    // Modify the expectedRequestRate if needed.
    // It needs to be at least 10 and a multiple of 10 because
    //                --------------------------------
    // exactly every 0.1 second a gating block needs to be measured
    // (for the integrated loudness measurement).
    if (expectedRequestRate < 10)
        expectedRequestRate = 10;
    else
    {
        expectedRequestRate = (((expectedRequestRate-1) / 10) + 1)*10;
            // examples
            //  19 -> 20
            //  20 -> 20
            //  21 -> 30
    }
    // It also needs to be a divisor of the samplerate for accurate
    // M and S values (the integrated loudness (I value) would not be
    // affected by this inaccuracy.
    while (int(sampleRate) % expectedRequestRate != 0)
    {
        expectedRequestRate += 10;
        
        if (expectedRequestRate > sampleRate/2)
        {
            expectedRequestRate = 10;
            DBGT("Ebu128LoudnessMeter::prepareToPlay. Not possible to make "
                 "expectedRequestRate a multiple of 10 and a divisor of the "
                 "samplerate.")
            break;
        }
    }
    
    DBGT("Ebu128LoudnessMeter::prepareToPlay, "
         "expectedRequestRate = " + String(expectedRequestRate))
    
    // Figure out how many bins are needed.
    const int timeOfAccumulationForShortTerm = 3; // seconds.
        //Needed for the short term loudness measurement.
    numberOfBins = expectedRequestRate * timeOfAccumulationForShortTerm;
    numberOfSamplesPerBin = int (sampleRate / expectedRequestRate);
    numberOfSamplesInAllBins = numberOfBins * numberOfSamplesPerBin;
    
    numberOfBinsToCover100ms = int(0.1 * expectedRequestRate);
    DBGT("Ebu128LoudnessMeter::prepareToPlay, "
         "numberOfBinsToCover100ms = " + String(numberOfBinsToCover100ms));
    numberOfBinsToCover400ms = int(0.4 * expectedRequestRate);
    DBGT("Ebu128LoudnessMeter::prepareToPlay, "
         "numberOfBinsToCover400ms = " + String(numberOfBinsToCover400ms));
    numberOfSamplesIn400ms = numberOfBinsToCover400ms * numberOfSamplesPerBin;
    
    currentBin = 0;
    numberOfSamplesInTheCurrentBin = 0;
    numberOfBinsSinceLastGateMeasurement = 0;
    
    // Initialize the bins and the measurement values.
    bin.clear();
    averageOfTheLast3s.clear();
    averageOfTheLast400ms.clear();
    
    for (int k=0; k != numberOfInputChannels; ++k)
    {
        OwnedArray<double>* binsForTheKthChannel = new OwnedArray<double>;
        for (int i=0; i<numberOfBins; ++i)
        {
            binsForTheKthChannel->add(new double);
        }
        bin.add(binsForTheKthChannel);
        
        averageOfTheLast3s.add(new double);
        averageOfTheLast400ms.add(new double);
    }
    
    // Initialize the channel weighting.
    channelWeighting.clear();
    for (int k=0; k != numberOfInputChannels; ++k)
    {
        if (k==3 || k==4)
            // The left and right surround channels have a higher weight
            // because they seem louder to the human ear.
            channelWeighting.add(1.41);
        else
            channelWeighting.add(1.0);
    }
    
    // Initialize the loudness measurements (the values measured in LUFS).
    shortTermLoudness.clear();
    momentaryLoudness.clear();
    for (int k=0; k != numberOfInputChannels; ++k)
    {
        shortTermLoudness.add(-300.0f);
        momentaryLoudness.add(-300.0f);
    }
    
    relativeThreshold = absoluteThreshold;
    resetTheIntegratedLoudness();
}

void Ebu128LoudnessMeter::processBlock(juce::AudioSampleBuffer &buffer)
{
    // Copy the buffer, such that all upcoming calculations won't affect
    // the audio output. We want the audio output to be exactly the same
    // as the input!
    bufferForMeasurement = buffer; // This copies the audio to another memory
        // location using memcpy.
    
    // STEP 1: K-weighted filter.
    // -----------------------------
    
    // Apply the pre-filter.
    // This is the first part of the so called K-weighted filtering.
    preFilter.processBlock(bufferForMeasurement);
    
    // Apply the RLB filter.
    // This is the second part of the so called K-weighted filtering.
    revisedLowFrequencyBCurveFilter.processBlock(bufferForMeasurement);
    
    // TEMP
    // Copy back to buffer to listen if everything went well.
    //   buffer = bufferForMeasurement;
    // END TEMP
    
    // STEP 2: Mean square.
    // --------------------
    for (int k=0; k != bufferForMeasurement.getNumChannels(); ++k)
    {
        float* theKthChannelData = bufferForMeasurement.getSampleData (k);
        for (int i = 0; i != bufferForMeasurement.getNumSamples(); ++i)
            theKthChannelData[i] = theKthChannelData[i] * theKthChannelData[i];
    }
        
    // STEP 3: Accumulate the samples and put the sum(s) into the right bin(s).
    // ------------------------------------------------------------------------
    
    // If the new samples from the bufferForMeasurement can all be added
    // to the same bin.
    if (numberOfSamplesInTheCurrentBin + bufferForMeasurement.getNumSamples() 
        < numberOfSamplesPerBin)
    {
        for (int k=0; k != bufferForMeasurement.getNumChannels(); ++k)
        {
            float* bufferOfChannelK = bufferForMeasurement.getSampleData (k);
            double* theBinToSumTo = bin[k]->getUnchecked(currentBin);
            for (int i=0; i != bufferForMeasurement.getNumSamples(); ++i)
            {
                *theBinToSumTo += bufferOfChannelK[i];
            }
        }
        numberOfSamplesInTheCurrentBin += bufferForMeasurement.getNumSamples();    
    }
    
    // If the new samples are split up between two (or more (which would be a
    // strange setup)) bins.
    else        
    {
        int positionInBuffer = 0;
        bool remainingSamplesInBuffer = true;
        while (remainingSamplesInBuffer)
        {
            // Figure out if the remaining samples in the buffer can all be
            // accumulated to the current bin.
            int numberOfSamplesLeftInTheBuffer = bufferForMeasurement.getNumSamples()-positionInBuffer;
            int numberOfSamplesToPutIntoTheCurrentBin;
            if (numberOfSamplesLeftInTheBuffer
                    < numberOfSamplesPerBin - numberOfSamplesInTheCurrentBin )
            {
                // If all the samples from the buffer can be added to the
                // current bin.
                numberOfSamplesToPutIntoTheCurrentBin = numberOfSamplesLeftInTheBuffer;
                remainingSamplesInBuffer = false;
            }
            else
            {
                // Accumulate samples to the current bin until it is full.
                numberOfSamplesToPutIntoTheCurrentBin = numberOfSamplesPerBin - numberOfSamplesInTheCurrentBin;
            }
            
            // Add the samples to the bin.
            for (int k=0; k != bufferForMeasurement.getNumChannels(); ++k)
            {
                float* bufferOfChannelK = bufferForMeasurement.getSampleData (k);
                double* theBinToSumTo = bin[k]->getUnchecked(currentBin);
                for (int i=positionInBuffer; 
                     i != positionInBuffer+numberOfSamplesToPutIntoTheCurrentBin;
                     ++i)
                {
                    *theBinToSumTo += bufferOfChannelK[i];
                }
            }
            numberOfSamplesInTheCurrentBin += numberOfSamplesToPutIntoTheCurrentBin;
            
            if (remainingSamplesInBuffer)
            {
                positionInBuffer = positionInBuffer
                                   + numberOfSamplesToPutIntoTheCurrentBin;
                
                // We have completely filled a bin.
                // This is the instant the larger sums need to be updated.
                for (int k=0; k != bufferForMeasurement.getNumChannels(); ++k)
                {
                    double sumOfAllBins = 0.0;
                        // which covers the last 3s.
                    
                    for (int b=0; b != numberOfBins; ++b)
                    {
                        sumOfAllBins += *(bin[k]->getUnchecked(b));
                    }
                    *(averageOfTheLast3s[k]) = sumOfAllBins / numberOfSamplesInAllBins;
                    
                    double sumOfBinsToCoverTheLast400ms = 0.0;
                    for (int d=0; d != numberOfBinsToCover400ms; ++d)
                    {
                        // The index for the bin.
                        int b = currentBin-d;
                            // this might be negative right now.
                        int n = numberOfBins;
                        b = (b%n + n)%n;
                            // b = b mod n (in the mathematical sense).
                            // Not negative anymore.
                            //
                            // Now 0 <= b < numberOfBins.
                            // Example: b=-5, n=30
                            //  b%n = -5
                            //  (b%n +n)%n = 25%30 = 25
                            //
                            // Example: b=16, n=30
                            //  b%n = 16
                            //  (b%n +n)%n = 46%30 = 16
                        
                        sumOfBinsToCoverTheLast400ms += *(bin[k]->getUnchecked(b));
                    }
                    *(averageOfTheLast400ms[k]) = sumOfBinsToCoverTheLast400ms / numberOfSamplesIn400ms;
                }
                
                // INTEGRATED LOUDNESS
                // ===================
                // For the integrated loudness measurement, every 100ms
                // we have to observe a gating window of length 400ms.
                // We call this window 'gating black', according to BS.1770-2
                if (numberOfBinsSinceLastGateMeasurement == numberOfBinsToCover100ms)
                {
                    numberOfBinsSinceLastGateMeasurement = 0;
                    
                    // Figure out if the current 400ms gated window
                    // fulfills the equation
                    //   l_j > /Gamma_a
                    // ( see ITU-R BS.1770-2 equation (4) ).
                    
                    // Calculate the weighted sum of the current block,
                    // (in 120725_integrated_loudness_revisited.tif, I call
                    // this s_j)
                    double weightedSumOfCurrentBlock = 0.0;
                    const int numberOfChannels = averageOfTheLast400ms.size();
                    for (int k=0; k != numberOfChannels; ++k)
                    {
                        weightedSumOfCurrentBlock += channelWeighting[k] * *averageOfTheLast400ms[k];
                    }
                    
                    // Calculate the j'th gating block loudness l_j
                    double loudnessOfCurrentBlock = -0.691 + 10.*std::log10(weightedSumOfCurrentBlock);
                    
                    // Recalculate the relative threshold, if needed.
                    if (loudnessOfCurrentBlock > absoluteThreshold)
                    {
                        ++numberOfBlocksToCalculateRelativeThreshold;
                        sumOfAllBlocksToCalculateRelativeThreshold += weightedSumOfCurrentBlock;
                        
                        // According to the definition of the relative
                        // threshold in ITU-R BS.1770-2, page 6.
                        relativeThreshold = -10.691 + 10.*std::log10(sumOfAllBlocksToCalculateRelativeThreshold/numberOfBlocksToCalculateRelativeThreshold);
                    }
                    
                    // Add the loudness of the current block to the histogram
                    if (loudnessOfCurrentBlock > lowestBlockLoudnessToConsider &&
                        loudnessOfCurrentBlock < highestBlockLoudnessToConsider)
                    {
                        const int binToAddItTo = floor((loudnessOfCurrentBlock-lowestBlockLoudnessToConsider)/histogramLoudnessStepSize);
                        histogramOfBlockLoudness[binToAddItTo] += 1;
                    }
                    
                    
                    // Recalculate the gated loudness.
                    const int binToStart = ceil((relativeThreshold - lowestBlockLoudnessToConsider)/histogramLoudnessStepSize);
                    if (binToStart < histogramOfBlockLoudness.size())
                    {
                        double loudnessOfBin = lowestBlockLoudnessToConsider + (binToStart + 0.5)*histogramLoudnessStepSize;
                        double weightedSumOfBin = pow(10.0, (loudnessOfBin + 0.691)/10.0);
                        int nrOfBlocks = 0;
                        double sumForIntegratedLoudness = 0.0;
                        for (int i = binToStart;
                             i < histogramOfBlockLoudness.size(); ++i)
                        {
                            const int nrOfBlocksInBin = histogramOfBlockLoudness[i];
                            nrOfBlocks += nrOfBlocksInBin;
                            sumForIntegratedLoudness += nrOfBlocksInBin * weightedSumOfBin;
                            
                            weightedSumOfBin *= histogramWeightedSumStepFactor;
                        }
                        
//                        DBGT("weightedSumOfLastBin (used) = "
//                             + String(weightedSumOfBin))
//                        DBGT("weightedSumOfLastBin (directly calculated) = "
//                             + String(pow(10.0, (lowestBlockLoudnessToConsider + (histogramOfBlockLoudness.size() + 0.5)*histogramLoudnessStepSize + 0.691)/10.0)))
                        
                        integratedLoudness = float(-0.691 + 10.*std::log10(sumForIntegratedLoudness/nrOfBlocks));
                    }

                }
                else
                    ++numberOfBinsSinceLastGateMeasurement;
                
                // Move on to the next bin
                currentBin = (currentBin + 1) % numberOfBins;
                // Set it to zero.
                for (int k=0; k != bufferForMeasurement.getNumChannels(); ++k)
                {
                    *(bin[k]->getUnchecked(currentBin)) = 0.0;
                }
                numberOfSamplesInTheCurrentBin = 0;
            }
        }
    }
}

const Array<float>& Ebu128LoudnessMeter::getShortTermLoudnessForIndividualChannels()
{
    // calculate the short term loudness
    for (int k=0; k != shortTermLoudness.size(); ++k)
    {
        // This refers to equation (2) in ITU-R BS.1770-2
        float kthChannelShortTermLoudness = float(-0.691 + 10.* std::log10(*averageOfTheLast3s[k]));
        shortTermLoudness.set(k, kthChannelShortTermLoudness);
    }
    
    return shortTermLoudness;
}

float Ebu128LoudnessMeter::getShortTermLoudness()
{
    // calculate the short term loudness
    double weightedSum = 0.0;
    for (int k=0; k != averageOfTheLast3s.size(); ++k)
    {
        weightedSum += channelWeighting[k] * *averageOfTheLast3s[k];
    }
    
    if (weightedSum > 0.0f)
    {
        // This refers to equation (2) in ITU-R BS.1770-2
        return jmax(float(-0.691 + 10.* std::log10(weightedSum)), minimalReturnValue);
    }
    else
    {
        // Since returning a value of -nan most probably would lead to
        // a malfunction, return a minimal return value.
        return minimalReturnValue;
    }
}

const Array<float>& Ebu128LoudnessMeter::getMomentaryLoudness()
{
    float kthChannelMomentaryLoudness;
    
    // calculate the momentary loudness
    for (int k=0; k != momentaryLoudness.size(); ++k)
    {
        if (*averageOfTheLast400ms[k] > 0.0f)
        {
            // This refers to equation (2) in ITU-R BS.1770-2
            kthChannelMomentaryLoudness = jmax(float(-0.691 + 10.* std::log10(*averageOfTheLast400ms[k])), minimalReturnValue);
        }
        else
        {
            kthChannelMomentaryLoudness = minimalReturnValue;
        }
        momentaryLoudness.set(k, kthChannelMomentaryLoudness);
    }
    
    return momentaryLoudness;
}

float Ebu128LoudnessMeter::getIntegratedLoudness()
{
    return integratedLoudness;
}

void Ebu128LoudnessMeter::resetTheIntegratedLoudness()
{
    numberOfBlocksToCalculateRelativeThreshold = 0;
    sumOfAllBlocksToCalculateRelativeThreshold = 0.0;
    
    for (int i=0; i<histogramOfBlockLoudness.size(); ++i)
    {
        histogramOfBlockLoudness[i] = 0;
    }
    
    integratedLoudness = -300.0f;
}
