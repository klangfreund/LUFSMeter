/*
 ===============================================================================
 
 Macros.h
 
 
 By Samuel Gaehwiler from Klangfreund.
 Used in the klangfreund.com/lufsmeter/

 License: MIT

 I'd be happy to hear about your usage of this code!
 -> klangfreund.com/contact/
 
 -------------------------------------------------------------------------------
 
 The MIT License (MIT)
 
 Copyright (c) 2018 Klangfreund, Samuel Gaehwiler
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
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
