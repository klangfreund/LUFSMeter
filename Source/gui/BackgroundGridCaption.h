/*
 ===============================================================================
 
 BackgroundGridCaption.h
 
 
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


#ifndef __BACKGROUND_GRID_CAPTION__
#define __BACKGROUND_GRID_CAPTION__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Macros.h"


//==============================================================================
/**
 Let this component spread from the top to the bottom of the window.
*/
class BackgroundGridCaption  : public Component,
                               public Value::Listener
{
public:
    BackgroundGridCaption (const int distanceBetweenLevelBarAndTop_,
                           const int distanceBetweenLevelBarAndBottom_,
                           const Value & minLoudnessToReferTo,
                           const Value & maxLoudnessToReferTo);
    
    ~BackgroundGridCaption ();

    void paint (Graphics& g);
    
private:
    void valueChanged (Value & value);
    
    int distanceBetweenLevelBarAndTop;
    int distanceBetweenLevelBarAndBottom;
    Value minLoudness;
    Value maxLoudness;
    int numberOfLines;

};


#endif  // __BACKGROUND_GRID_CAPTION__
