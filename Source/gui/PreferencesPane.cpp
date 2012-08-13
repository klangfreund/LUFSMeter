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
    backgroundColour (Colours::green)
{
    addAndMakeVisible(&showOrHidePreferences);  
    
    addAndMakeVisible(&loudnessBarSize);
}

PreferencesPane::~PreferencesPane ()
{
}

//==============================================================================
void PreferencesPane::paint (Graphics& g)
{
    // Draw the background
    g.setColour(backgroundColour);
    g.fillAll();
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
    const int buttonsize = 20;
    showOrHidePreferences.setBounds(getWidth() - buttonsize, 2, buttonsize, buttonsize);
    
    const int leftBorder = 5;
    const int topBorder = 5;
    const int sliderHeight = 20;
    loudnessBarSize.setBounds(leftBorder, topBorder, getWidth()-buttonsize, sliderHeight);
}