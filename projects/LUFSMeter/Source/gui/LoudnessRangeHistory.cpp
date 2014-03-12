/*
 ===============================================================================
 
 LoudnessHistory.cpp
 
 
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


#include "LoudnessRangeHistory.h"


//==============================================================================
LoudnessRangeHistory::LoudnessRangeHistory (const Value & startValueToReferTo,
                                            const Value & endValueToReferTo,
                                            const Value & minLoudnessToReferTo,
                                            const Value & maxLoudnessToReferTo)
: LoudnessHistory(startValueToReferTo,
                  minLoudnessToReferTo,
                  maxLoudnessToReferTo)
{
}

LoudnessRangeHistory::~LoudnessRangeHistory ()
{
}

void LoudnessRangeHistory::paint (Graphics& g)
{
    
    // Draw the graph.
    g.setColour (colour);
    float currentX = getWidth();
    float currentY = *mostRecentYPosition;
    float nextX;
    float nextY;
    std::vector<float>::iterator nextYPosition = mostRecentYPosition;
    
    do
    {
        if (nextYPosition == circularBufferForYPositions.begin())
        {
            nextYPosition = circularBufferForYPositions.end();
        }
        nextYPosition--;
        
        nextX = floor(currentX - numberOfPixelsBetweenTwoPoints);
        // Without "floor", the line segments are not joined,
        // a little space between the segments is visible.
        // TODO: Report this to Jules.
        nextY = *nextYPosition;
        
        g.drawLine(currentX, currentY, nextX, nextY, lineThickness);
        
        // Prepare for the next iteration.
        currentX = nextX;
        currentY = nextY;
    }
    while (nextYPosition != mostRecentYPosition);
}