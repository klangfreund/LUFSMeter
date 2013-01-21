/*
 ===============================================================================
 
 LUFSMeterAudioProcessor.cpp
 
 
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


#include "LUFSMeterAudioProcessor.h"
#include "LUFSMeterAudioProcessorEditor.h"


//==============================================================================
LUFSMeterAudioProcessor::LUFSMeterAudioProcessor()
:
    // Set up some default values..
    lastUIWidth (600),
    lastUIHeight (300),
    loudnessBarWidth (50),
    loudnessBarMinValue (var(-41)),
    loudnessBarMaxValue (var(-14))
{
}

LUFSMeterAudioProcessor::~LUFSMeterAudioProcessor()
{
}

//==============================================================================
const String LUFSMeterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int LUFSMeterAudioProcessor::getNumParameters()
{
    return 0;
}

float LUFSMeterAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void LUFSMeterAudioProcessor::setParameter (int index, float newValue)
{
}

const String LUFSMeterAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String LUFSMeterAudioProcessor::getParameterText (int index)
{
    return String::empty;
}

const String LUFSMeterAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String LUFSMeterAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool LUFSMeterAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool LUFSMeterAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool LUFSMeterAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool LUFSMeterAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

int LUFSMeterAudioProcessor::getNumPrograms()
{
    return 0;
}

int LUFSMeterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LUFSMeterAudioProcessor::setCurrentProgram (int index)
{
}

const String LUFSMeterAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void LUFSMeterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void LUFSMeterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    DBGT("LUFSMeterAudioProcessor::prepareToPlay called")
    
    //TODO
    int expectedRequestRate = 20;
    
    ebu128LoudnessMeter.prepareToPlay(sampleRate, 
                                      getNumInputChannels(), 
                                      samplesPerBlock, 
                                      expectedRequestRate);
    
//    Array<var>* theArrayInside = momentaryLoudnessValues.getValue().getArray();
//    theArrayInside->clear();
//    double TODO_minimalLoudness = -300;
//    int numberOfInputChannels = getNumInputChannels();
//    theArrayInside->insertMultiple (0, var (TODO_minimalLoudness), numberOfInputChannels);
}

void LUFSMeterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void LUFSMeterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ebu128LoudnessMeter.processBlock(buffer);    

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
    
    // ask the host for the current time so we can display it...
    AudioPlayHead::CurrentPositionInfo newTime;
    
    if (getPlayHead() != 0 && getPlayHead()->getCurrentPosition (newTime))
    {
        // Successfully got the current time from the host..
        lastPosInfo = newTime;
    }
    else
    {
        // If the host fails to fill-in the current time, we'll just clear it to a default..
        lastPosInfo.resetToDefault();
    }
}

//==============================================================================
bool LUFSMeterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* LUFSMeterAudioProcessor::createEditor()
{
    return new LUFSMeterAudioProcessorEditor (this);
}

//==============================================================================
void LUFSMeterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    // Create an outer XML element..
    XmlElement xml ("MYPLUGINSETTINGS");
    
    // add some attributes to it..
    xml.setAttribute ("uiWidth", lastUIWidth);
    xml.setAttribute ("uiHeight", lastUIHeight);
    xml.setAttribute("loudnessBarWidth", loudnessBarWidth);
    xml.setAttribute("loudnessBarMinValue", int(loudnessBarMinValue.getValue()));
    xml.setAttribute("loudnessBarMaxValue", int(loudnessBarMaxValue.getValue()));
    
    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xml, destData);
}

void LUFSMeterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != 0)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName ("MYPLUGINSETTINGS"))
        {
            // ok, now pull out our parameters..
            lastUIWidth  = xmlState->getIntAttribute ("uiWidth", lastUIWidth);
            lastUIHeight = xmlState->getIntAttribute ("uiHeight", lastUIHeight);
            loudnessBarWidth = xmlState->getIntAttribute ("loudnessBarWidth", loudnessBarWidth);
            loudnessBarMinValue.setValue (xmlState->getIntAttribute ("loudnessBarMinValue"));
            loudnessBarMaxValue.setValue(xmlState->getIntAttribute ("loudnessBarMaxValue"));
        }
    }
}

float LUFSMeterAudioProcessor::getShortTermLoudness()
{
    return ebu128LoudnessMeter.getShortTermLoudness();
}

const Array<float>& LUFSMeterAudioProcessor::getMomentaryLoudness()
{
    return ebu128LoudnessMeter.getMomentaryLoudness();
}

float LUFSMeterAudioProcessor::getIntegratedLoudness()
{
    return ebu128LoudnessMeter.getIntegratedLoudness();
}

void LUFSMeterAudioProcessor::reset()
{
    ebu128LoudnessMeter.reset();
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LUFSMeterAudioProcessor();
}
