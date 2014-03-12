/*
 ===============================================================================
 
 LoudnessHistory.h
 
 
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


#ifndef __LOUDNESS_RANGE_HISTORY__
#define __LOUDNESS_RANGE_HISTORY__

#include "../MacrosAndJuceHeaders.h"
#include "LoudnessHistory.h"
#include <vector>
#include <algorithm> // to use std::rotate


//==============================================================================
/**
   A graph that shows the course of a value over time for a given time interval.
*/
class LoudnessRangeHistory  : public LoudnessHistory
{
public:
    LoudnessRangeHistory (const Value & startValueToReferTo,
                          const Value & endValueToReferTo,
                          const Value & minLoudnessToReferTo,
                          const Value & maxLoudnessToReferTo);
    
    ~LoudnessRangeHistory ();
    
//    Value & getLevelValueObject ();
//    
//    void setColour (const Colour & newColour);
//
//    int getDesiredRefreshIntervalInMilliseconds ();
//    void timerCallback ();
//    
//    void resized () override;
    void virtual paint (Graphics& g) override;
//    
//    void reset ();
    
private:
//    void valueChanged (Value & value);
//    
//    /** Recalculates the values 'stretch' and 'offset' by the values of
//     'minLoudness' and 'maxLoudness'.
//     
//     The two values stretch and offset define a linear mapping
//     f(x) = stretch * x + offset
//     for which
//     f(minimumLevel) = 0
//     f(maximumLevel) = 1 .
//     */
//    void determineStretchAndOffset ();
//    
//    void stretchTheHistoryGraph ();
//    
//    Value currentLevelValue;
//    Value minLoudness;
//    Value maxLoudness;
//    
//    float stretch;
//    float offset;
//    
//    Colour colour;
//    
//    /** The time interval that is displayed.
//     Measured in seconds.
//     */
//    int specifiedTimeRange;
//    float lineThickness;
//    float desiredNumberOfPixelsBetweenTwoPoints;
//    int textBoxWidth;
//    int distanceBetweenLeftBorderAndText;
//    
//    float fullTimeRange;
//    float numberOfPixelsBetweenTwoPoints;
//    
//    int desiredRefreshIntervalInMilliseconds;
//    
//    /** A circular buffer to hold the past level values.
//     
//     Holds the y coordinates for the graph.
//     */
//    std::vector<float> circularBufferForYPositions;
//    std::vector<float>::iterator mostRecentYPosition;
//    
//    int distanceBetweenGraphAndBottom;
};


#endif  // __LOUDNESS_RANGE_HISTORY__
