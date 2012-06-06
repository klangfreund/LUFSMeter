/*
 ===============================================================================
 
 LevelBar.cpp
 
 
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


#include "LevelBar.h"


//==============================================================================
LevelBar::LevelBar (const Value & levelValueToReferTo)
  : maximumLevel (-14.0f),
    minimumLevel (-41.0f),
    currentLevel (minimumLevel),
    previousLevel (minimumLevel)
{
    levelValue.referTo(levelValueToReferTo);
    
    levelValue.addListener(this);

    // These two values define a linear mapping
    //    f(x) = stretch * x + offset
    // for which
    //    f(minimumLevel) = 0
    //    f(maximumLevel) = 1
    stretch = 1.0f/(maximumLevel-minimumLevel);
    offset = -minimumLevel * stretch;
}

LevelBar::~LevelBar ()
{
    levelValue.removeListener(this);
}

Value & LevelBar::getLevelValueObject ()
{
    return levelValue;
}

void LevelBar::valueChanged (Value & value)
{
    currentLevel = value.getValue();
    
    // Ensure that the currentLevel is in the interval
    // [minimumLevel, maximumLevel].
    currentLevel = jmax(currentLevel, minimumLevel);
    currentLevel = jmin(currentLevel, maximumLevel);
    
    if (currentLevel != previousLevel)
    {
//        float topBorderInPercent = stretch*jmax(currentLevel,previousLevel) + offset;
//        float bottomBorderInPercent = stretch*jmin(currentLevel,previousLevel) + offset;
//        
//        const int topLeftX = 0;
//        const int topLeftY = floor((1-topBorderInPercent) * (float) getHeight()) -3;
//        const int heightOfSectionToDraw = ceil((topBorderInPercent-bottomBorderInPercent) * (float) getHeight()) + 3;
//        
        previousLevel = currentLevel;
//    
//        repaint(topLeftX, topLeftY, getWidth(), heightOfSectionToDraw);
        
        // Mesurements showed that it is more CPU efficient to draw the whole
        // bar and not only the section that has changed.
        repaint();
    }
}

//==============================================================================
void LevelBar::paint (Graphics& g)
{
    const float width = (float) getWidth();
    const float height = (float) getHeight();
    
    // Draw a background
//    g.setColour(Colours::black);
//    float x = 0.0f;
//    float y = 0.0f;
//    float cornerSize = 3.0f;
//    g.fillRoundedRectangle(x, y, width, height, cornerSize);
    
    float barHeightInPercent = stretch*currentLevel + offset;
    g.setColour(Colours::green);
    const float topLeftX = 0.0f;
    float topLeftY = (1.0f - barHeightInPercent) * height;
    float bottomY = height;
    g.fillRect(topLeftX,
               topLeftY,
               width,
               bottomY-topLeftY);
}