/*
 ===============================================================================
 
 LevelHistory.cpp
 
 
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


#include "LevelHistory.h"


//==============================================================================
LevelHistory::LevelHistory (const Value & levelValueToReferTo)
  : currentLevelValue (var(0.0f)),
    maximumLevel (-14.0f),
    minimumLevel (-41.0f),
//    timeRange (240),
    specifiedTimeRange (20),
    lineThickness (2.0f),
//    desiredNumberOfPixelsBetweenTwoPoints (3.0f),
    desiredNumberOfPixelsBetweenTwoPoints (6.0f),
    textBoxWidth (40),
    distanceBetweenLeftBorderAndText (3),
    mostRecentYPosition (circularBufferForYPositions.begin()),
    distanceBetweenGraphAndBottom (32)
{
    currentLevelValue.referTo (levelValueToReferTo);
    
    // These two values define a linear mapping
    //    f(x) = stretch * x + offset
    // for which
    //    f(minimumLevel) = 0
    //    f(maximumLevel) = 1
    stretch = 1.0f/(maximumLevel-minimumLevel);
    offset = -minimumLevel * stretch;
    
//    // To prevent some crap at the initial stage
//    heightOfGraph = 10;
    
    // Memory allocation for the circularLevelBuffer as well as starting
    // the timer will be done by this.
    resized();
}

LevelHistory::~LevelHistory ()
{
}

Value & LevelHistory::getLevelValueObject ()
{
    return currentLevelValue;
}

void LevelHistory::timerCallback()
{
    // Ensure that the currentLevel is in the interval
    // [minimumLevel, maximumLevel].
    float currentLevel = jmax(float(currentLevelValue.getValue()), minimumLevel);
    currentLevel = jmin(currentLevel, maximumLevel);
    
    float levelHeightInPercent = stretch*currentLevel + offset;
    
    float yPositionForCurrentLevel = (1.0f - levelHeightInPercent)*heightOfGraph;
    
    
    // Adjust the position of the iterator...
    mostRecentYPosition++;
    if (mostRecentYPosition == circularBufferForYPositions.end())
    {
        mostRecentYPosition = circularBufferForYPositions.begin();
    }
    // ...and put the current level into the circular buffer.
    *mostRecentYPosition = yPositionForCurrentLevel;

    // Mark this component as "dirty" to make the OS send a paint message soon.
    const int xPos = 0;
    const int yPos = 0;
    repaint(xPos, yPos, getWidth(), heightOfGraph + lineThickness);
}

//==============================================================================
void LevelHistory::resized()
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
    int oldHeightOfGraph = heightOfGraph;
    
    heightOfGraph = jmax(getHeight() - distanceBetweenGraphAndBottom, 0);
    
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
    // The copy of the old state.
    std::vector<float> oldCircularBufferForYPositions (circularBufferForYPositions);
    
    // Preallocate memory needed for the pastLevelValues.
    std::vector<float>::size_type numberOfValues = numberOfPoints;
    circularBufferForYPositions.resize(numberOfValues, heightOfGraph);
     
    // Rescaling, part 2
    // =================
    if (circularBufferForYPositions.size() > 1 
        && oldCircularBufferForYPositions.size() > 1 
        && oldHeightOfGraph > 0)
    {
        // Figure out the new yPosition of every entry in the buffer.
    
        double stretchFactorYDirection = double(heightOfGraph)/double(oldHeightOfGraph);
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
    
    // Start the timer which will refresh the GUI elements.
    const int refreshIntervalInMilliseconds = 1000*fullTimeRange/numberOfPoints;
    startTimer(refreshIntervalInMilliseconds);
        // Will set the new interval, starting right now.
}

void LevelHistory::paint (Graphics& g)
{
    // Draw the vertical lines and the time caption
    if (getWidth() > distanceBetweenLeftBorderAndText + textBoxWidth)
    {
        // Draw the left most vertical line behind the graph.
        g.setColour(Colour(40,40,40));
        const float xOfFirstLine = floor(distanceBetweenLeftBorderAndText + textBoxWidth/2.0) + 0.5;
            // "+0.5" causes the line to lie on a row of pixels and not between.
        g.drawLine(xOfFirstLine, 0, xOfFirstLine, heightOfGraph + 8);
        
        // Draw the text
        g.setColour(Colour(60,60,60));
        float fontHeight = 16.0f;
        const Font font (fontHeight);
        g.setFont(font);
        const int maximumNumberOfTextLines = 1;
        const float topLeftY = getHeight() - 1.5f * fontHeight;
        
        g.drawFittedText("-" + String(specifiedTimeRange) + "s", 
                         distanceBetweenLeftBorderAndText, 
                         topLeftY, 
                         textBoxWidth, 
                         fontHeight, 
                         juce::Justification::centred,
                         maximumNumberOfTextLines);
        
        // Draw the middle line and text
        int minimalDistanceBetweenText = 6; // pixels
        if (getWidth() > distanceBetweenLeftBorderAndText + 2*textBoxWidth + minimalDistanceBetweenText)
        {
            // Draw the vertical line behind the graph.
            g.setColour(Colour(40,40,40));
            const float xOfSecondLine = floor((getWidth() - xOfFirstLine)/2.0 + xOfFirstLine) + 0.5;
            // "+0.5" causes the line to lie on a row of pixels and not between.
            g.drawLine(xOfSecondLine, 0, xOfSecondLine, heightOfGraph + 8);
            
            // Draw the text
            g.setColour(Colour(60,60,60));
            g.setFont(font);
            g.drawFittedText("-" + String(specifiedTimeRange/2) + "s", 
                             xOfSecondLine - 0.5*textBoxWidth, 
                             topLeftY, 
                             textBoxWidth, 
                             fontHeight, 
                             juce::Justification::centred,
                             maximumNumberOfTextLines);
        }
    }
    
    // Draw the graph.
    g.setColour(Colours::green);
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

void LevelHistory::reset ()
{
    for (std::vector<float>::iterator i = circularBufferForYPositions.begin(); 
         i != circularBufferForYPositions.end(); 
         i++)
    {
        *i = heightOfGraph;
    }
}