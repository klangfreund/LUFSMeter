/*
 ===============================================================================
 
 Macros.h
 
 
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


#ifndef __LUFSMETER_MACROS__
#define __LUFSMETER_MACROS__

#include "../JuceLibraryCode/JuceHeader.h"

// Sams debug macro which also has a time stamp.
#if JUCE_DEBUG || DOXYGEN
/** Writes a string to the standard error stream, together with the time
 of occurence.
 This is only compiled in a debug build.
 @see Logger::outputDebugString
 */
    #define DBGT(dbgtext)  { Time currentTime = Time::getCurrentTime(); bool includeDate = true; bool includeTime = true; bool includeSeconds = true; bool use24HourClock = true; DBG(currentTime.toString(includeDate, includeTime, includeSeconds, use24HourClock) + ": " + dbgtext) }

#else
    #define DBGT(dbgtext)

#endif

#endif // __LUFSMETER_MACROS__
