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
#include "Ebu128LoudnessMeter.h"

//==============================================================================
/**
*/
class Ebu128LoudnessMeterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Ebu128LoudnessMeterAudioProcessorEditor (Ebu128LoudnessMeterAudioProcessor&);
    ~Ebu128LoudnessMeterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Ebu128LoudnessMeterAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ebu128LoudnessMeterAudioProcessorEditor)
};
