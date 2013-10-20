/*
 ===============================================================================
 
 PreferencesPane.h
  
 
 This file is part of the LUFS Meter audio measurement plugin.
 Copyright 2012 by Klangfreund, Samuel Gaehwiler.
 
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

#ifndef __PREFERENCES_PANE__
#define __PREFERENCES_PANE__

#include "../MacrosAndJuceHeaders.h"
#include "AnimatedSidePanel.h"
#include "LoudnessBarRangeSlider.h"



//==============================================================================
/**
*/
class PreferencesPane  : public AnimatedSidePanel
{
public:
    PreferencesPane (const Value& loudnessBarWidth,
                     const Value& loudnessBarMinValue,
                     const Value& loudnessBarMaxValue);
    
    ~PreferencesPane ();
    
    void resized();
    
private:
    Slider loudnessBarSize;
    LoudnessBarRangeSlider loudnessBarRange;   
};


#endif  // __PREFERENCES_PANE__
