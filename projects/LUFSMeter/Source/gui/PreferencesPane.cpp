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
PreferencesPane::PreferencesPane ()
:
    //backgroundColour (Colours::lightgoldenrodyellow),
    backgroundColour (Colours::darkgreen),
    preferencesTitleHeight (20),
    borderSize (3),
    topRightHandleWidth (20)
{
    setAlpha(0.5);
    
    showOrHidePreferences.setButtonText("Preferences");
    showOrHidePreferences.setColour(TextButton::buttonColourId, Colours::black);
    showOrHidePreferences.setColour(TextButton::textColourOffId, Colours::white);
    addAndMakeVisible(&showOrHidePreferences);
 
    const bool isReadOnly = false;
    const int textEntryBoxWidth = 0;
    const int textEntryBoxHeight = 0; 
    //loudnessBarSize.setTextBoxStyle(Slider::NoTextBox, isReadOnly, textEntryBoxWidth, textEntryBoxHeight);
    loudnessBarSize.setPopupDisplayEnabled(true, this);
    loudnessBarSize.setTextValueSuffix(" pixels");
    loudnessBarSize.setSliderStyle(Slider::LinearBar);
    addAndMakeVisible(&loudnessBarSize);
    
    loudnessBarRange.setTextBoxStyle(Slider::NoTextBox, isReadOnly, textEntryBoxWidth, textEntryBoxHeight);
    loudnessBarRange.setPopupDisplayEnabled(true, this);
    loudnessBarRange.setTextValueSuffix(" LUFS");
    addAndMakeVisible(&loudnessBarRange);
}

PreferencesPane::~PreferencesPane ()
{
}

//==============================================================================
void PreferencesPane::paint (Graphics& g)
{
    // Draw the background
    // ===================
    const int roundedCornerRadius = (preferencesTitleHeight + 2*borderSize)/2;
    g.setColour(backgroundColour);
    // Draw the main area
    g.fillRoundedRectangle(0, 0, getWidth() - topRightHandleWidth, getHeight(), roundedCornerRadius);
    // Remove the rounded corners on the left
    g.fillRect(0, 0, roundedCornerRadius, getHeight());
    // Draw the handle on the top right
    g.fillRoundedRectangle(0, 0, getWidth(), preferencesTitleHeight + 2*borderSize, roundedCornerRadius);
}

void PreferencesPane::mouseDown(const juce::MouseEvent &event)
{
//    backgroundColour = Colours::green;
//    
//    ComponentAnimator& animator = Desktop::getInstance().getAnimator();
//    
//    const Rectangle<int> finalBounds = Rectangle<int>(50, 100, 200, 50);
//    const float finalAlpha = 0.5f;
//    const int animationDurationMilliseconds = 1000;
//    const bool useProxyComponent = false;
//    const double startSpeed = 0.0;
//    const double endSpeed = 0.0;
//    animator.animateComponent(this, finalBounds, finalAlpha, animationDurationMilliseconds, useProxyComponent , startSpeed, endSpeed);
    
}

void PreferencesPane::resized()
{
//    const int leftBorder = 5;
//    const int topBorder = 5; 
    showOrHidePreferences.setBounds(borderSize, borderSize, getWidth() - 2*borderSize, preferencesTitleHeight);
    
    const int sliderHeight = 20;
//    const int rightBorder = 20;
    const int loudnessBarSizeY = 2*borderSize + preferencesTitleHeight;
    const int sliderWidth = getWidth() - 2*borderSize - topRightHandleWidth;
    loudnessBarSize.setBounds(borderSize, loudnessBarSizeY, sliderWidth, sliderHeight);
    
    const int loudnessBarRangeY = loudnessBarSizeY + sliderHeight + borderSize;
    loudnessBarRange.setBounds(borderSize, loudnessBarRangeY, sliderWidth, sliderHeight);
}