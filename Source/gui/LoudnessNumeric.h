/*
 ===============================================================================
 
 LoudnessNumeric.h
 
 
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


#ifndef __LOUDNESS_NUMERIC__
#define __LOUDNESS_NUMERIC__

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Macros.h"



//==============================================================================
/**
*/
class LoudnessNumeric  : public Component,
                         public Value::Listener
{
public:
    LoudnessNumeric ();
    
    ~LoudnessNumeric ();
    
    Value & getLevelValueObject ();
    
    void valueChanged (Value & value);

    void paint (Graphics& g);
    
private:
    
    Value levelValue;
    String currentLevelText;
    String previousLevelText;
};


#endif  // __LOUDNESS_NUMERIC__
