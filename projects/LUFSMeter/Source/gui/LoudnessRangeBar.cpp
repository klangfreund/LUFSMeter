/*
 ===============================================================================
 
 LoudnessBar.cpp
 
 
 This file is part of the LUFS Meter audio measurement plugin.
 Copyright 2011-14 by Klangfreund, Samuel Gaehwiler.
 
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


#include "LoudnessRangeBar.h"


//==============================================================================
LoudnessRangeBar::LoudnessRangeBar (const Value & startValueToReferTo,
                                    const Value & endValueToReferTo,
                                    const Value & minValueToReferTo,
                                    const Value & maxValueToReferTo)
:   colour (Colours::green),
    currentStart (minValueToReferTo.getValue()),
    currentEnd (minValueToReferTo.getValue()),
    previousStart (currentStart),
    previousEnd (currentEnd)
{
    startValue.referTo(startValueToReferTo);
    startValue.addListener(this);
    endValue.referTo(endValueToReferTo);
    endValue.addListener(this);
    
    minLoudness.referTo(minValueToReferTo);
    minLoudness.addListener(this);
    maxLoudness.referTo(maxValueToReferTo);
    maxLoudness.addListener(this);

    determineStretchAndOffset();
}

LoudnessRangeBar::~LoudnessRangeBar()
{
    startValue.removeListener (this);
    endValue.removeListener (this);
}

Value & LoudnessRangeBar::getStartValueObject ()
{
    return startValue;
}

Value & LoudnessRangeBar::getEndValueObject ()
{
    return endValue;
}

void LoudnessRangeBar::valueChanged (Value & value)
{
    if (value.refersToSameSourceAs (startValue))
    {
        // Ensure that the currentLoudness is in the interval
        // [minimumLevel, maximumLevel].
        currentStart = jlimit(float(minLoudness.getValue()),
                              float(maxLoudness.getValue()),
                              float(value.getValue()));
        
        if (currentStart != previousStart)
        {
            //        float topBorderInPercent = stretch*jmax(currentLoudness,previousLoudness) + offset;
            //        float bottomBorderInPercent = stretch*jmin(currentLoudness,previousLoudness) + offset;
            //        
            //        const int topLeftX = 0;
            //        const int topLeftY = floor((1-topBorderInPercent) * (float) getHeight()) -3;
            //        const int heightOfSectionToDraw = ceil((topBorderInPercent-bottomBorderInPercent) * (float) getHeight()) + 3;
            //        
            previousStart = currentStart;
            //    
            //        repaint(topLeftX, topLeftY, getWidth(), heightOfSectionToDraw);
            
            // Mesurements showed that it is more CPU efficient to draw the whole
            // bar and not only the section that has changed.
            repaint();
        }
    }
    else if (value.refersToSameSourceAs (endValue))
    {
        // Ensure that the currentEnd is in the interval
        // [minimumLevel, maximumLevel].
        currentEnd = jlimit(float(minLoudness.getValue()),
                            float(maxLoudness.getValue()),
                            float(value.getValue()));
        
        if (currentEnd != previousEnd)
        {
            previousEnd = currentEnd;

            // Mesurements showed that it is more CPU efficient to draw the whole
            // bar and not only the section that has changed.
            repaint();
        }
    }
    else if (value.refersToSameSourceAs (minLoudness) || value.refersToSameSourceAs (maxLoudness))
    {
        determineStretchAndOffset();
        repaint();
    }
}

void LoudnessRangeBar::setColour (const Colour & newColour)
{
    colour = newColour;
}

//==============================================================================
void LoudnessRangeBar::paint (Graphics& g)
{
    const float width = (float) getWidth();
    const float height = (float) getHeight();
    
    // Draw a background
//    g.setColour(Colours::black);
//    float x = 0.0f;
//    float y = 0.0f;
//    float cornerSize = 3.0f;
//    g.fillRoundedRectangle(x, y, width, height, cornerSize);
    
    g.setColour(colour);
    const float topLeftX = 0.0f;
    float barTop = stretch*currentEnd + offset;
    float topLeftY = (1.0f - barTop) * height;
    float barBottom = stretch*currentStart + offset;
    float bottomY = (1.0f - barBottom) * height;
    g.fillRect(topLeftX,
               topLeftY,
               width,
               bottomY-topLeftY);
}

void LoudnessRangeBar::determineStretchAndOffset()
{
    // These two values define a linear mapping
    //    f(x) = stretch * x + offset
    // for which
    //    f(minimumLevel) = 0
    //    f(maximumLevel) = 1
    stretch = 1.0f/(double(maxLoudness.getValue()) - double(minLoudness.getValue()));
    offset = -double(minLoudness.getValue()) * stretch;
}