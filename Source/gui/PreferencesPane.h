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

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Macros.h"



//==============================================================================
/**
*/
class PreferencesPane  : public Component
{
public:
    PreferencesPane ();
    
    ~PreferencesPane ();

    void paint (Graphics& g);
    
    void mouseDown(const juce::MouseEvent &event);
    
    void resized();
    
    ToggleButton showOrHidePreferences;
    Slider loudnessBarSize;
    
private:
    
    // Temp
    Colour backgroundColour;
    
};


#endif  // __PREFERENCES_PANE__
