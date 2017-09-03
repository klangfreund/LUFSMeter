/*
 ===============================================================================
 
 Macros.h
 
 
 This file is part of the LUFS Meter audio measurement plugin.
 Copyright 2011-17 by Klangfreund, Samuel Gaehwiler.
 
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

#ifndef    JUCE_ENABLE_LIVE_CONSTANT_EDITOR
#define JUCE_ENABLE_LIVE_CONSTANT_EDITOR 0
#endif

#ifdef LUFSMETER_STANDALONE // This preprocessor definition is set as a
// compiler argument (Open the LUFSMeterStandalone.jucer in the Introjucer
// and go to the Config -> LUFSMeterStandalone) when this file is compiled for
// the standalone version of the LUFS Meter.
  #include "../../LUFSMeterStandalone/JuceLibraryCode/JuceHeader.h"
#else
  #include "../JuceLibraryCode/JuceHeader.h"
#endif

#include <string.h> // Contains strrchr, which is used in DEB.

/** Sams debug macro which also has a time stamp.
	
	Writes a string to the standard error stream, together with the time
    of occurence.
    This is only compiled in a debug build.
    @see Logger::outputDebugString
 */
// Windows Debug
#if (JUCE_DEBUG || DOXYGEN) && JUCE_WINDOWS // Windows doesn't understand __func__
		#define DEB(dbgtext)  { Time currentTime = Time::getCurrentTime(); const bool includeDate = false; const bool includeTime = true; const bool includeSeconds = true; const bool use24HourClock = true; String filename = strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__; DBG(currentTime.toString(includeDate, includeTime, includeSeconds, use24HourClock) + ", " + filename + ":" + String(__LINE__) + ": " + dbgtext) }
// Mac Debug
#elif (JUCE_DEBUG || DOXYGEN)
		#define DEB(dbgtext)  { Time currentTime = Time::getCurrentTime(); const bool includeDate = false; const bool includeTime = true; const bool includeSeconds = true; const bool use24HourClock = true; String filename = strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__; DBG(currentTime.toString(includeDate, includeTime, includeSeconds, use24HourClock) + ", " + filename + "::" + __func__ + ":" + String(__LINE__) + ": " + dbgtext) }
// Release
#else
    #define DEB(dbgtext)

#endif

#endif // __LUFSMETER_MACROS__
