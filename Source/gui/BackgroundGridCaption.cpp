/*
 ===============================================================================
 
 BackgroundGridCaption.cpp
 
 
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


#include "BackgroundGridCaption.h"


//==============================================================================
BackgroundGridCaption::BackgroundGridCaption (int distanceBetweenLevelBarAndTop_,
                                              int distanceBetweenLevelBarAndBottom_)
  : distanceBetweenLevelBarAndTop (distanceBetweenLevelBarAndTop_),
    distanceBetweenLevelBarAndBottom (distanceBetweenLevelBarAndBottom_),
    numberOfLines (10)
{
}

BackgroundGridCaption::~BackgroundGridCaption ()
{
}

//==============================================================================
void BackgroundGridCaption::paint (Graphics& g)
{   
    // Draw a black background to "cut" the horizontal lines.
    g.fillAll(Colours::black);
    
    //g.setColour(Colour(40,40,40));
    g.setColour(Colour(60,60,60));
    float fontHeight = 16.0f;
    float halfFontHeight = fontHeight/2.0f;
    const Font font (fontHeight);
    g.setFont(font);
    const int maximumNumberOfTextLines = 1;
    const float topLeftX = 0.0f;
    const float distanceBetweenTopAndBottomLine = getHeight() - distanceBetweenLevelBarAndTop - distanceBetweenLevelBarAndBottom;
    int caption = -14;
    for (int i=0; i<numberOfLines; i++)
    {
        float positionOfLine = floor( (int)( distanceBetweenLevelBarAndTop + (float)i * distanceBetweenTopAndBottomLine / (numberOfLines-1) )) - 0.5;
        // - 0.5 ensures that the line will be drawn on a single row of pixels. 
        // Otherwise, two rows of pixels would have been used for one line.
        float topLeftY = positionOfLine - halfFontHeight;
        g.drawFittedText(String(caption), 
                         topLeftX, 
                         topLeftY, 
                         getWidth(), 
                         fontHeight, 
                         juce::Justification::centred,
                         maximumNumberOfTextLines);
        
        caption -= 3;
    }
    
    // Print the units.
    g.drawFittedText("LUFS", 
                     topLeftX, 
                     getHeight() - 1.5f * fontHeight, 
                     getWidth(), 
                     fontHeight, 
                     juce::Justification::centred,
                     maximumNumberOfTextLines);
}