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


#include "AnimatedSidePanel.h"

//==============================================================================
AnimatedSidePanel::AnimatedSidePanel ()
  : movingPanelVisible (true)
{
    addAndMakeVisible (&movingPanel);
    
    showOrHideButton.setButtonText("Side Panel");
    showOrHideButton.setColour(TextButton::buttonColourId, Colours::black);
    showOrHideButton.setColour(TextButton::textColourOffId, Colours::white);
    showOrHideButton.addListener(this);
    movingPanel.addAndMakeVisible(&showOrHideButton);
}

AnimatedSidePanel::~AnimatedSidePanel ()
{
}

void AnimatedSidePanel::paint (Graphics& g)
{
}

void AnimatedSidePanel::resized()
{
    movingPanel.setSize(getWidth(), getHeight());
    
    showOrHideButton.setBounds(3, 3, getWidth() - 6, 20);
    
    /*
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
     */
}

void AnimatedSidePanel::buttonClicked (Button* button)
{
    if (button == &showOrHideButton)
    {
        int movingPanelXPosition;
        
        if (!movingPanelVisible)
        {
            movingPanelXPosition = 0;
            movingPanelVisible = true;
        }
        else
        {
            movingPanelXPosition = -380;
            movingPanelVisible = false;
        }
        
        ComponentAnimator& animator = Desktop::getInstance().getAnimator();
        
        const Rectangle<int> finalBounds = Rectangle<int>(movingPanelXPosition,
                                                          0,
                                                          getWidth(),
                                                          getHeight());
        const float finalAlpha = 0.5f;
        const int animationDurationMilliseconds = 300;
        const bool useProxyComponent = false;
        const double startSpeed = 0.0;
        const double endSpeed = 0.0;
        animator.animateComponent(&movingPanel, finalBounds, finalAlpha, animationDurationMilliseconds, useProxyComponent , startSpeed, endSpeed);
    }
}


//==============================================================================
AnimatedSidePanel::MovingPanel::MovingPanel ()
:   backgroundColour (Colours::lightgoldenrodyellow),
//backgroundColour (Colours::darkgreen),
titleHeight (20),
borderSize (3),
topRightHandleWidth (titleHeight)
{
}

AnimatedSidePanel::MovingPanel::~MovingPanel ()
{
}

void AnimatedSidePanel::MovingPanel::paint (Graphics& g)
{
    setAlpha(0.5);
    
    // Draw the background
    // ===================
    const int roundedCornerRadius = (titleHeight + 2 * borderSize) / 2;
    g.setColour(backgroundColour);
    // Draw the main area
    g.fillRoundedRectangle(0, 0, getWidth() - topRightHandleWidth, getHeight(), roundedCornerRadius);
    // Remove the rounded corners on the left
    g.fillRect(0, 0, roundedCornerRadius, getHeight());
    // Draw the handle on the top right
    g.fillRoundedRectangle(0, 0, getWidth(), titleHeight + 2*borderSize, roundedCornerRadius);
    
}

void AnimatedSidePanel::MovingPanel::resized()
{
    
}