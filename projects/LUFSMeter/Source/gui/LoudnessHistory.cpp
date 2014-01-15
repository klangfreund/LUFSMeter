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


#include "LoudnessHistory.h"


//==============================================================================
LoudnessHistory::LoudnessHistory (const Value & loudnessValueToReferTo,
                                  const Value & minLoudnessToReferTo,
                                  const Value & maxLoudnessToReferTo)
  : currentLevelValue (var(0.0f)),
//    timeRange (240),
    colour (Colours::green),
    specifiedTimeRange (20), // seconds
    lineThickness (2.0f),
//    desiredNumberOfPixelsBetweenTwoPoints (3.0f),
    desiredNumberOfPixelsBetweenTwoPoints (6.0f),
    textBoxWidth (40),
    distanceBetweenLeftBorderAndText (3),
    desiredRefreshIntervalInMilliseconds (1000),
    mostRecentYPosition (circularBufferForYPositions.begin()),
    distanceBetweenGraphAndBottom (32)
{
    currentLevelValue.referTo (loudnessValueToReferTo);
    minLoudness.referTo (minLoudnessToReferTo);
    minLoudness.addListener(this);
    maxLoudness.referTo (maxLoudnessToReferTo);
    maxLoudness.addListener(this);

    DEB("minLoudness = " + minLoudness.getValue().toString())
    DEB("maxLoudness = " + maxLoudness.getValue().toString())
    
    determineStretchAndOffset();
    
    // Memory allocation for the circularLevelBuffer as well as starting
    // the timer will be done by this.
    resized();
}

LoudnessHistory::~LoudnessHistory ()
{
}

Value & LoudnessHistory::getLevelValueObject ()
{
    return currentLevelValue;
}

void LoudnessHistory::setColour (const Colour & newColour)
{
    colour = newColour;
}

int LoudnessHistory::getDesiredRefreshIntervalInMilliseconds ()
{
    return desiredRefreshIntervalInMilliseconds;
}

void LoudnessHistory::timerCallback()
{
    // Ensure that the currentLevel is in the interval
    // [minimumLevel, maximumLevel].
//    float currentLevel = jmax(float(currentLevelValue.getValue()), float(minLoudness.getValue()));
//    currentLevel = jmin(currentLevel, float(maxLoudness.getValue()));
    float currentLevel = currentLevelValue.getValue();
    
    float levelHeightInPercent = stretch*currentLevel + offset;
    
    float yPositionForCurrentLevel = (1.0f - levelHeightInPercent)*getHeight();
    
    
    // Adjust the position of the iterator...
    mostRecentYPosition++;
    if (mostRecentYPosition == circularBufferForYPositions.end())
    {
        mostRecentYPosition = circularBufferForYPositions.begin();
    }
    // ...and put the current level into the circular buffer.
    *mostRecentYPosition = yPositionForCurrentLevel;

    // Mark this component as "dirty" to make the OS send a paint message soon.
    repaint();
}

//==============================================================================
void LoudnessHistory::resized()
{
    // Figure out the full time range.
    if (getWidth() > distanceBetweenLeftBorderAndText + textBoxWidth)
    {
        double borderToLeftVerticalLine = distanceBetweenLeftBorderAndText + textBoxWidth/2.0;
        fullTimeRange = getWidth()/(getWidth() - borderToLeftVerticalLine) * specifiedTimeRange;
    }
    else
    {
        fullTimeRange = specifiedTimeRange;
    }
    
    // Some old values, needed for the rescaling
    int oldHeight = getHeight();
    
    
    int numberOfPoints = getWidth()/desiredNumberOfPixelsBetweenTwoPoints + 1;
    numberOfPixelsBetweenTwoPoints = getWidth()/jmax(double(numberOfPoints-1.0),1.0);
    
    // Rescaling, part 1
    // =================
    if (circularBufferForYPositions.size() > 1)
    {
        // Dimensions changed -> Stretching of the current graph is needed.
        // Therefore this strategy:
        
        // Make a copy of circularBufferForYPositions and interpolate
        // ----------------------------------------------------------
        
        // Sort the buffer, such that the most recent value is at the end.
        // I.e. the oldest value is at the begin and the newest one at end()-1.
        if (mostRecentYPosition + 1 != circularBufferForYPositions.end())
        {
            std::rotate(circularBufferForYPositions.begin(), 
                        mostRecentYPosition + 1, 
                        circularBufferForYPositions.end());
        }
    }
    // Copy this old (sorted) state.
    std::vector<float> oldCircularBufferForYPositions (circularBufferForYPositions);
    
    // Preallocate memory needed for the circularBufferForYPositions.
    std::vector<float>::size_type numberOfValues = numberOfPoints;
    circularBufferForYPositions.resize(numberOfValues);
    reset();
     
    // Rescaling, part 2
    // =================
    if (circularBufferForYPositions.size() > 1 
        && oldCircularBufferForYPositions.size() > 1 
        && oldHeight > 0)
    {
        // Figure out the new yPosition of every entry in the buffer.
    
        double stretchFactorYDirection = double(getHeight())/double(oldHeight);
        double numberOfPixelsBetweenOldValues = double(getWidth())/double(oldCircularBufferForYPositions.size() - 1);
        double xPosition = 0.0;
        
        // Set all the values but the last.
        for (std::vector<float>::iterator newYPosition = circularBufferForYPositions.begin();
             newYPosition != circularBufferForYPositions.end()-1;
             newYPosition++)
        {
            // Find the old value, that is closest to the new xPosition from
            // the left.
            int indexInTheOldBuffer = floor(xPosition/numberOfPixelsBetweenOldValues);
            double delta = xPosition/numberOfPixelsBetweenOldValues - indexInTheOldBuffer;
                // delta lies in the range [0.0, 1.0[ and describes the position
                // of the newYPosition between the neighbouring values of the
                // old circular buffer.
            jassert(indexInTheOldBuffer >= 0);
            if (indexInTheOldBuffer < oldCircularBufferForYPositions.size() - 1)
            {
                jassert(indexInTheOldBuffer < oldCircularBufferForYPositions.size() - 1);
                // Linear interpolation between two points.
                *newYPosition = (1.0 - delta) * oldCircularBufferForYPositions[indexInTheOldBuffer] + delta * oldCircularBufferForYPositions[indexInTheOldBuffer + 1];
            }
            else
            {
                // indexInTheOldBuffer >= oldCircularBufferForYPositions.size() - 1
                // might happen if delta == 0.0.
                // In this case, the
                // oldCircularBufferForYPositions[indexInTheOldBuffer + 1]
                // will point to a not allocated memory region.
                *newYPosition = oldCircularBufferForYPositions[indexInTheOldBuffer];
            }
            
            // We also need to stretch into the y direction.
            *newYPosition = *newYPosition * stretchFactorYDirection;
            
            xPosition += numberOfPixelsBetweenTwoPoints;
        }
        
        // Set the last value.
        *(circularBufferForYPositions.end()-1) = *(oldCircularBufferForYPositions.end()-1) * stretchFactorYDirection;
    }

    // Set the itator to the first value
    mostRecentYPosition = circularBufferForYPositions.end() - 1;
    
    // Calculate the time interval, at which the timerCallback() will be called by a instance of LoudnessHistoryGroup.
    desiredRefreshIntervalInMilliseconds = 1000*fullTimeRange/numberOfPoints;
}

void LoudnessHistory::paint (Graphics& g)
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

void LoudnessHistory::reset ()
{
    float minLoudnessToSet = -300.0f;
    float levelHeightInPercent = stretch*minLoudnessToSet + offset;
    float yPosition = (1.0f - levelHeightInPercent)*getHeight();
    
    
    for (std::vector<float>::iterator i = circularBufferForYPositions.begin(); 
         i != circularBufferForYPositions.end(); 
         i++)
    {
        *i = yPosition;
    }
}

void LoudnessHistory::valueChanged (Value & value)
{
    const float oldStretch = stretch;
    const float oldOffset = offset;
    
    // minLoudness or maxLoudness has changed.
    // Therefore:
    determineStretchAndOffset();
    
    // And rescale
    for (std::vector<float>::iterator yPos = circularBufferForYPositions.begin();
         yPos != circularBufferForYPositions.end(); ++yPos)
    {
        // Derivation on 120817_loudness_history_min_max_value_changes.tif
        *yPos = (1.0 - (stretch/oldStretch * (1.0 - *yPos/getHeight() - oldOffset) + offset)) * getHeight();
    }
}

void LoudnessHistory::determineStretchAndOffset()
{
    // These two values define a linear mapping
    //    f(x) = stretch * x + offset
    // for which
    //    f(minimumLevel) = 0
    //    f(maximumLevel) = 1
    stretch = 1.0f/(double(maxLoudness.getValue()) - double(minLoudness.getValue()));
    offset = -double(minLoudness.getValue()) * stretch;
}