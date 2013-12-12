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
                                  const Value& loudnessBarMaxValue,
                                  const Value& showIntegratedLoudnessHistoryValue,
                                  const Value& showShortTermLoudnessHistoryValue,
                                  const Value& showMomentaryLoudnessHistoryValue)
  : AnimatedSidePanel("Preferences"),
    loudnessHistoryGroup (String::empty, "History Graph"),
    showIntegratedLoudnessHistory ("I"),
    showShortTimeLoudnessHistory ("S"),
    showMomentaryLoudnessHistory ("M")
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
    loudnessBarSize.setColour(Slider::trackColourId, Colours::black);
    addAndMakeVisible (&loudnessBarSize);

    loudnessBarRange.setRange (-100, 0.0, 1);
    loudnessBarRange.getMinValueObject().referTo (loudnessBarMinValue);
    loudnessBarRange.getMaxValueObject().referTo (loudnessBarMaxValue);
    loudnessBarRange.setColour (Slider::thumbColourId, Colours::black);
    loudnessBarRange.setTextBoxStyle (Slider::NoTextBox, isReadOnly, textEntryBoxWidth, textEntryBoxHeight);
    loudnessBarRange.setPopupDisplayEnabled (true, this);
    loudnessBarRange.setTextValueSuffix (" LUFS");
    loudnessBarRange.setColour(Slider::trackColourId, Colours::black);
    addAndMakeVisible (&loudnessBarRange);
    
    
    Colour loudnessHistoryGroupColour = Colours::black; //Colour (200, 200, 200);
    loudnessHistoryGroup.setColour(GroupComponent::outlineColourId, loudnessHistoryGroupColour);
    loudnessHistoryGroup.setColour(GroupComponent::textColourId, loudnessHistoryGroupColour);
    addAndMakeVisible (&loudnessHistoryGroup);
    
    Colour buttonOnColour = Colours::black;
    Colour textColourOn = Colours::lightgrey;
    Colour buttonOffColour = Colours::grey;
    Colour textColourOff = Colours::black;
    showIntegratedLoudnessHistory.setClickingTogglesState (true);
    showIntegratedLoudnessHistory.getToggleStateValue().referTo (showIntegratedLoudnessHistoryValue);
    showIntegratedLoudnessHistory.setWantsKeyboardFocus (false);
    showIntegratedLoudnessHistory.setColour(TextButton::buttonOnColourId, buttonOnColour);
    showIntegratedLoudnessHistory.setColour(TextButton::textColourOnId, textColourOn);
    showIntegratedLoudnessHistory.setColour(TextButton::buttonColourId, buttonOffColour);
    showIntegratedLoudnessHistory.setColour(TextButton::textColourOffId, textColourOff);
    loudnessHistoryGroup.addAndMakeVisible (&showIntegratedLoudnessHistory);
    
    showShortTimeLoudnessHistory.setClickingTogglesState (true);
    showShortTimeLoudnessHistory.getToggleStateValue().referTo (showShortTermLoudnessHistoryValue);
    showShortTimeLoudnessHistory.setWantsKeyboardFocus (false);
    showShortTimeLoudnessHistory.setColour(TextButton::buttonOnColourId, buttonOnColour);
    showShortTimeLoudnessHistory.setColour(TextButton::textColourOnId, textColourOn);
    showShortTimeLoudnessHistory.setColour(TextButton::buttonColourId, buttonOffColour);
    showShortTimeLoudnessHistory.setColour(TextButton::textColourOffId, textColourOff);
    loudnessHistoryGroup.addAndMakeVisible (&showShortTimeLoudnessHistory);
    
    showMomentaryLoudnessHistory.setClickingTogglesState (true);
    showMomentaryLoudnessHistory.getToggleStateValue().referTo (showMomentaryLoudnessHistoryValue);
    showMomentaryLoudnessHistory.setWantsKeyboardFocus (false);
    showMomentaryLoudnessHistory.setColour(TextButton::buttonOnColourId, buttonOnColour);
    showMomentaryLoudnessHistory.setColour(TextButton::textColourOnId, textColourOn);
    showMomentaryLoudnessHistory.setColour(TextButton::buttonColourId, buttonOffColour);
    showMomentaryLoudnessHistory.setColour(TextButton::textColourOffId, textColourOff);
    loudnessHistoryGroup.addAndMakeVisible (&showMomentaryLoudnessHistory);
    
//    showIntegratedLoudnessLabel.setColour(Label::textColourId, Colours::lightgrey);
//    showIntegratedLoudnessLabel.setJustificationType(Justification::centred);
//    addAndMakeVisible(&showIntegratedLoudnessLabel);
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
    
    loudnessHistoryGroup.setBounds(borderSize, loudnessBarRangeY + sliderHeight + borderSize, sliderWidth, 15 + 24 + 10);
    
    const int buttonSize = 24;
    const int spaceBetweenButtons = 6;
    int buttonX = (loudnessHistoryGroup.getWidth() - 3 * buttonSize - 2 * spaceBetweenButtons) / 2;
    const int buttonY = 15; // loudnessBarRangeY + sliderHeight + borderSize + 6;
    showIntegratedLoudnessHistory.setBounds (buttonX, buttonY, buttonSize, buttonSize);
    buttonX += buttonSize + borderSize + 6;
    showShortTimeLoudnessHistory.setBounds(buttonX, buttonY, buttonSize, buttonSize);
    buttonX += buttonSize + borderSize + 6;
    showMomentaryLoudnessHistory.setBounds(buttonX, buttonY, buttonSize, buttonSize);
    //showIntegratedLoudnessLabel.setBounds(borderSize, toggleButtonsY + 20, 20, 20);
}