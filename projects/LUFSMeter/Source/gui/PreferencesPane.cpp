/*
 ===============================================================================
 
 PreferencesPane.cpp
 
 
 This file is part of the LUFS Meter audio measurement plugin.
 Copyright 2012 by Klangfreund, Samuel Gaehwiler.
 
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


#include "PreferencesPane.h"


//==============================================================================
PreferencesPane::PreferencesPane (const Value& loudnessBarWidth,
                                  const Value& loudnessBarMinValue,
                                  const Value& loudnessBarMaxValue)
  :  AnimatedSidePanel("Preferences"),
     showIntegratedLoudnessLabel( String::empty, "I")
{
    const bool isReadOnly = false;
    const int textEntryBoxWidth = 0;
    const int textEntryBoxHeight = 0;
    
    loudnessBarSize.setRange (5.0, 300.0, 1);
    loudnessBarSize.getValueObject().referTo(loudnessBarWidth);
    loudnessBarSize.setColour(Slider::thumbColourId, Colours::black);
    loudnessBarSize.setPopupDisplayEnabled(true, this);
    loudnessBarSize.setTextValueSuffix(" pixels");
    loudnessBarSize.setTextBoxStyle(Slider::NoTextBox, isReadOnly, textEntryBoxWidth, textEntryBoxHeight);
    addAndMakeVisible(&loudnessBarSize);

    loudnessBarRange.setRange (-100, 0.0, 1);
    loudnessBarRange.getMinValueObject().referTo(loudnessBarMinValue);
    loudnessBarRange.getMaxValueObject().referTo(loudnessBarMaxValue);
    loudnessBarRange.setColour(Slider::thumbColourId, Colours::black);
    loudnessBarRange.setTextBoxStyle(Slider::NoTextBox, isReadOnly, textEntryBoxWidth, textEntryBoxHeight);
    loudnessBarRange.setPopupDisplayEnabled(true, this);
    loudnessBarRange.setTextValueSuffix(" LUFS");
    addAndMakeVisible(&loudnessBarRange);
    
    //showIntegratedLoudnessHistory.setButtonText ("I");
    showIntegratedLoudnessHistory.setWantsKeyboardFocus (false);
    addAndMakeVisible(&showIntegratedLoudnessHistory);
    showIntegratedLoudnessLabel.setColour(Label::textColourId, Colours::lightgrey);
    showIntegratedLoudnessLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&showIntegratedLoudnessLabel);
    //showIntegratedLoudnessLabel.attachToComponent(&showIntegratedLoudnessHistory, false);
}

PreferencesPane::~PreferencesPane ()
{
}

void PreferencesPane::resized()
{
    AnimatedSidePanel::resized();
    
    const int sliderHeight = 20;
    const int loudnessBarSizeY = 2*borderSize + titleHeight;
    const int sliderWidth = getWidth() - 2*borderSize - topRightHandleWidth;
    loudnessBarSize.setBounds (borderSize, loudnessBarSizeY, sliderWidth, sliderHeight);
    
    const int loudnessBarRangeY = loudnessBarSizeY + sliderHeight + borderSize;
    loudnessBarRange.setBounds (borderSize, loudnessBarRangeY, sliderWidth, sliderHeight);
    
    const int toggleButtonsY = loudnessBarRangeY + sliderHeight + borderSize;
    showIntegratedLoudnessHistory.setBounds (borderSize, toggleButtonsY, 20, 20);
    showIntegratedLoudnessLabel.setBounds(borderSize, toggleButtonsY + 20, 20, 20);
}