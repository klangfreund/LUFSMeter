/*
 ===============================================================================
 
 Ebu128LoudnessMeter


 By Samuel Gaehwiler from Klangfreund.
 Used in the klangfreund.com/lufsmeter/

 License: MIT

 I'd be happy to hear about your usage of this code!
 -> klangfreund.com/contact/
 
 -------------------------------------------------------------------------------
 
 The MIT License (MIT)
 
 Copyright (c) 2018 Klangfreund, Samuel Gaehwiler
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ===============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "MacrosAndJuceHeaders.h"
#include "filters/SecondOrderIIRFilter.h"
#include <map>
#include <vector>

using std::map;
using std::vector;


//==============================================================================
/**
*/
class Ebu128LoudnessMeterAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Ebu128LoudnessMeterAudioProcessor();
    ~Ebu128LoudnessMeterAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    
    float getShortTermLoudness() const;
    float getMaximumShortTermLoudness() const;
    
    vector<float>& getMomentaryLoudnessForIndividualChannels();
    float getMomentaryLoudness() const;
    float getMaximumMomentaryLoudness() const;
    
    float getIntegratedLoudness() const;
    
    float getLoudnessRangeStart() const;
    float getLoudnessRangeEnd() const;
    float getLoudnessRange() const;
    
    /** Returns the time passed since the last reset.
        In seconds.
     */
    float getMeasurementDuration() const;

    void setFreezeLoudnessRangeOnSilence (bool freeze);
    
    void reset1();
    
    

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ebu128LoudnessMeterAudioProcessor)
    
    
    
    static int round (double d);
    
    /** The buffer given to processBlock() will be copied to this buffer, such
     that the filtering and squaring won't affect the audio output. I.e. thanks
     to this, the audio will pass through this without getting changed.
     
     It also stores the number of input channels implicitely, set in prepareToPlay.
     */
    juce::AudioSampleBuffer bufferForMeasurement;
    
    SecondOrderIIRFilter preFilter;
    SecondOrderIIRFilter revisedLowFrequencyBCurveFilter;

    int numberOfBins;
    int numberOfSamplesPerBin;
    int numberOfSamplesInAllBins;
    int numberOfBinsToCover400ms;
    int numberOfSamplesIn400ms;
    
    int numberOfBinsToCover100ms;
    int numberOfBinsSinceLastGateMeasurementForI;
    // int millisecondsSinceLastGateMeasurementForLRA;
    
    /** The duration of the current measurement.
        
        duration * 0.1 = the measurement duration in seconds.
      */
    int measurementDuration;
    
    /**
     After the samples are filtered and squared, they need to be
     accumulated.
     For the measurement of the short-term loudness, the previous
     3 seconds of samples need to be accumulated. For the other
     measurements shorter windows are used.
     
     This task could be solved using a ring buffer capable of
     holding 3 seconds of (multi-channel) audio and accumulate the
     samples every time the GUI wants to display the measurement.
     
     But it's easier on the CPU and needs far less memory if not
     all samples are stored but only the summation of all the
     samples in a 1/(GUI refresh rate) s - e.g. 1/20 s - time window.
     If we then need to determine the sum of all samples of the previous
     3s, we only have to accumulate 60 values.
     The downside of this method is that the displayed measurement
     has an accuracy jitter of max. e.g. 1/20 s. I guess this isn't
     an issue since GUI elements are refreshed asynchron anyway.
     Just to be clear, the accuracy of the measurement isn't effected.
     But if you ask for a measurement at time t, it will be the
     accurate measurement at time t - dt, where dt \in e.g. [0, 1/20s].
     */
    vector<vector<double>> bin;
    
    int currentBin;
    int numberOfSamplesInTheCurrentBin;
    
    /*
     The average of the filtered and squared samples of the last
     3 seconds.
     A value for each channel.
     */
    vector<double> averageOfTheLast3s;
    
    /*
     The average of the filtered and squared samples of the last
     400 milliseconds.
     A value for each channel.
     */
    vector<double> averageOfTheLast400ms;
    
    vector<double> channelWeighting;
    
    vector<float> momentaryLoudnessForIndividualChannels;
    
    /** If there is no signal at all, the methods getShortTermLoudness() and
     getMomentaryLoudness() would perform a log10(0) which would result in
     a value -nan. To avoid this, the return value of this methods will be
     set to minimalReturnValue.
     */
    static const float minimalReturnValue;
    
    /** A gated window needs to be bigger than this value to
     contribute to the calculation of the relative threshold.
     
     absoluteThreshold = Gamma_a = -70 LUFS.
     */
    static const double absoluteThreshold;
    
    int numberOfBlocksToCalculateRelativeThreshold;
    double sumOfAllBlocksToCalculateRelativeThreshold;
    double relativeThreshold;
    
    int numberOfBlocksToCalculateRelativeThresholdLRA;
    double sumOfAllBlocksToCalculateRelativeThresholdLRA;
    double relativeThresholdLRA;
    
    /** A lower bound for the histograms (for I and LRA).
        If a measured block has a value lower than this, it will not be
        considered in the calculation for I and LRA.

        Without the possibility to increase the pre-measurement-gain at any
        point after the measurement has started, this could have been set
        to the absoluteThreshold = -70 LUFS.
     */
    static const double lowestBlockLoudnessToConsider;
    
    /** Storage for the loudnesses of all 400ms blocks since the last reset.
     
     Because the relative threshold varies and all blocks with a loudness
     bigger than the relative threshold are needed to calculate the gated
     loudness (integrated loudness), it is mandatory to keep track of all
     block loudnesses.
     
     Adjacent bins are set apart by 0.1 LU which seems to be sufficient.
     
     Key value = Loudness * 10 (to get an integer value).
     */
    map<int,int> histogramOfBlockLoudness;
    
    /** The main loudness value of interest. */
    float integratedLoudness;

    float shortTermLoudness;
    float maximumShortTermLoudness;

    float momentaryLoudness;
    float maximumMomentaryLoudness;
    
    /** Like histogramOfBlockLoudness, but for the measurement of the
     loudness range.
     
     The histogramOfBlockLoudness can't be used simultaneous for the
     loudness range, because the measurement blocks for the loudness
     range need to be of length 3s. Vs 400ms.
     */
    map<int,int> histogramOfBlockLoudnessLRA;
    
    /**
     The return values for the corresponding get member functions.
     
     Loudness Range = loudnessRangeEnd - loudnessRangeStart.
     */
    float loudnessRangeStart;
    float loudnessRangeEnd;

    bool freezeLoudnessRangeOnSilence;
    bool currentBlockIsSilent;
    

};
