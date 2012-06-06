/*
 ===============================================================================
 
 LevelHistory.h
 
 
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


#ifndef __LEVEL_HISTORY__
#define __LEVEL_HISTORY__

#include <vector>
#include <algorithm> // to use std::rotate
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Macros.h"


//==============================================================================
/**
   A graph that shows the course of a value over time for a given period of
   time.
*/
class LevelHistory  : public Component,
                      public Timer
{
public:
    LevelHistory (const Value & levelValueToReferTo);
    
    ~LevelHistory ();
    
    Value & getLevelValueObject ();

    void timerCallback();
    void resized();
    void paint (Graphics& g);
    
    void reset ();
    
private:
    
    Value currentLevelValue;
    
    float maximumLevel;
    float minimumLevel;
    
    float stretch;
    float offset;
    
    /** The time interval that is displayed.
     Measured in seconds.
     */
    int specifiedTimeRange;
    float lineThickness;
    float desiredNumberOfPixelsBetweenTwoPoints;
    int textBoxWidth;
    int distanceBetweenLeftBorderAndText;
    
    float fullTimeRange;
    float numberOfPixelsBetweenTwoPoints;
    
    /** A circular buffer to hold the past level values.
     
     Holds the y coordinates for the graph.
     */
    std::vector<float> circularBufferForYPositions;
    std::vector<float>::iterator mostRecentYPosition;
    
    int distanceBetweenGraphAndBottom;
    int heightOfGraph;
};


#endif  // __LEVEL_HISTORY__
