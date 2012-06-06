/*
 ===============================================================================
 
 Main.cpp
 
 
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


#include "../../JuceLibraryCode/JuceHeader.h"
// Needed by the StandaloneFilterWindow:
// #include "../../JuceLibraryCode/JucePluginCharacteristics.h"

// #include "../../juce/modules/juce_audio_plugin_client/Standalone/juce_StandaloneFilterWindow.h"
#include "juce_StandaloneFilterWindow_modified.h"
// #include "juce_StandaloneFilterWindow.h"

//==============================================================================
class LUFSMeterStandaloneApplication  : public JUCEApplication
{
public:
    //==============================================================================
    LUFSMeterStandaloneApplication()
    {
    }

    ~LUFSMeterStandaloneApplication()
    {
    }

    //==============================================================================
    void initialise (const String& commandLine)
    {
        mainWindow = new StandaloneFilterWindow(JUCEApplication::getInstance()->getApplicationName(), Colours::lightgrey, nullptr);
        // ApplicationProperties::getInstance()->setStorageParameters (T("DemoAudioPluginStandalone"), String::empty, T("DemoAudioPluginStandalone"), 400, PropertiesFile::storeAsXML);
        //filterWindow = new StandaloneFilterWindow (T("DemoAudioPluginStandalone"), Colours::black);
        mainWindow->setTitleBarButtonsRequired (DocumentWindow::allButtons, false);
        mainWindow->setVisible (true);
        mainWindow->setResizable (true, true);        
    }

    void shutdown()
    {
        mainWindow = 0;
        //deleteAndZero (filterWindow);
        
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        quit();
    }

    //==============================================================================
    const String getApplicationName()
    {
        return "LUFS Meter";
    }

    const String getApplicationVersion()
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed()
    {
        return true;
    }

    void anotherInstanceStarted (const String& commandLine)
    {
        
    }

private:
    ScopedPointer <StandaloneFilterWindow> mainWindow; 
};

//==============================================================================
// This macro generates the main() routine that starts the app.
START_JUCE_APPLICATION(LUFSMeterStandaloneApplication)
