/*
 ===============================================================================
 
 LevelNumeric.cpp
 
 
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


#include "LevelNumeric.h"


//==============================================================================
LevelNumeric::LevelNumeric ()
{
    levelValue.addListener(this);
}

LevelNumeric::~LevelNumeric ()
{
    levelValue.removeListener(this);
}

Value & LevelNumeric::getLevelValueObject ()
{
    return levelValue;
}

void LevelNumeric::valueChanged (Value & value)
{
    const int numberOfDecimalPlaces = 2;
    currentLevelText = String((float)levelValue.getValue(), numberOfDecimalPlaces);
    
    if (currentLevelText != previousLevelText)
    {
        previousLevelText = currentLevelText;
        
        // Mark this component as "dirty" to make the OS send a paint message soon.
        repaint();
    }
}

//==============================================================================
void LevelNumeric::paint (Graphics& g)
{   
    // Temp, for debugging:
    // g.fillAll(Colours::red);
    
    // Draw the value as text
    g.setColour(Colours::green);
    float fontHeight = getHeight();
    const Font font (fontHeight);
    g.setFont(font);
    const int topLeftX = 0;
    const int topLeftY = 0;
    const int maximumNumberOfLines = 1;
    g.drawFittedText(currentLevelText, 
                     topLeftX, 
                     topLeftY, 
                     getWidth(), 
                     getHeight(), 
                     juce::Justification::centred,
                     maximumNumberOfLines);
}