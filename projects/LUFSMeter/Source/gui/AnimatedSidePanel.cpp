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
  : backgroundColour (Colours::lightgoldenrodyellow),
    //backgroundColour (Colours::darkgreen),
    titleHeight (20),
    borderSize (3),
    topRightHandleWidth (titleHeight),
    panelIsVisible (false),
    xPositionWhenHidden (0)
{
    //setAlwaysOnTop (true);
    
    //movingPanel.setBounds (-380, 0, 400, 300);
    //addAndMakeVisible (&movingPanel);
    
    showOrHideButton.setButtonText("Side Panel");
    showOrHideButton.setColour(TextButton::buttonColourId, Colours::black);
    showOrHideButton.setColour(TextButton::textColourOffId, Colours::white);
    showOrHideButton.setAlwaysOnTop (true);
    showOrHideButton.addListener(this);
    addAndMakeVisible(&showOrHideButton);
}

AnimatedSidePanel::~AnimatedSidePanel ()
{
}

void AnimatedSidePanel::paint (Graphics& g)
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

bool AnimatedSidePanel::hitTest(int x, int y)
{
    if (isPositiveAndNotGreaterThan(y, getHeight()))
    {
        if (isPositiveAndNotGreaterThan(x, getWidth() - topRightHandleWidth))
        {
            return true;
        }
        // If its on the handle on the top right
        if (isPositiveAndBelow(y, titleHeight + 2*borderSize)
            && isPositiveAndNotGreaterThan(x, getWidth()))
        {
            return true;
        }
    }

    return false;
}

void AnimatedSidePanel::resized()
{
    //movingPanel.setSize(getWidth(), getHeight());
    xPositionWhenHidden = getX();
    
    showOrHideButton.setBounds(3, 3, getWidth() - 6, 20);
}

void AnimatedSidePanel::buttonClicked (Button* button)
{
    if (button == &showOrHideButton)
    {
        int movingPanelXPosition;
        
        if (!panelIsVisible)
        {
            movingPanelXPosition = xPositionWhenHidden + 380;
            panelIsVisible = true;
            //toFront (true);
        }
        else
        {
            movingPanelXPosition = xPositionWhenHidden;
            panelIsVisible = false;
            //toBack();
        }
        
        ComponentAnimator& animator = Desktop::getInstance().getAnimator();
        
        const Rectangle<int> finalBounds = Rectangle<int>(movingPanelXPosition,
                                                          getY(),
                                                          getWidth(),
                                                          getHeight());
        const float finalAlpha = 0.5f;
        const int animationDurationMilliseconds = 300;
        const bool useProxyComponent = false;
        const double startSpeed = 0.0;
        const double endSpeed = 0.0;
        animator.animateComponent(this,
                                  finalBounds,
                                  finalAlpha,
                                  animationDurationMilliseconds,
                                  useProxyComponent ,
                                  startSpeed,
                                  endSpeed);
    }
}