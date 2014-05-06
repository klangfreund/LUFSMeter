.. author: Samuel Gaehwiler (klangfreund.com)

***********************************************************
How to set up the LUFS Meter or any new JUCE Plugin on OSX 
***********************************************************

OSX is my main development environment at the moment:
OSX 10.7.5
XCode 4.6

But most of these informations are also valid for other platforms.



0. Get the Core Audio Utility Classes 
=====================================

Original source: http://rawmaterialsoftware.com/viewtopic.php?f=8&t=9546&p=56679#p56677

0.1 Make sure you're running XCode 4.6 or later

0.2 Get the "Core Audio Utility Classes" ZIP file from Apple using the
    "Download Sample Code" button at
    https://developer.apple.com/library/mac/#samplecode/CoreAudioUtilityClasses/Introduction/Intro.html.
    The current version is Version 1.03 released on 2013-01-02.

0.3 The zip file contains installation instructions. It assumes that the 
    CoreAudio folder will be placed (hopefully permanently) in the 
    /Library/Developer folder.

0.4 -- not neccessary anymore --

0.5 To maintain backward compatibility, you may do the following. The 
    current Introjucer assumes that the following has been done.

    - Navigate to the /Applications/Xcode.app/Contents/Developer folder.
    - Create an Extras directory if said directory does not exist.
    - If a CoreAudio directory or symlink exists (with full path 
      /Applications/Xcode.app/Contents/Developer/Extras/CoreAudio),
      remove it (back it up first, though!).
    - Create a symlink via 
      sudo ln -sv /Library/Developer/CoreAudio /Applications/Xcode.app/Contents/Developer/Extras/
    - Note that modifying anything in the /Applications/Xcode.app 
      directory can invalidate Xcode's digital signature, which may 
      bring about strange behaviour with GateKeeper or the App Store. 
      It has not been a problem for me as the digital signature seems 
      to be validated only once during App Store installation... 
      but you have been warned.


**The projects provided in this repository should work now. The
following lines describe how they have been set up.**

-------



1. JUCE Basic Plugin as Audio Unit
==================================

1.1 Get Juce

1.2 Use the Introjucer to set up an audio plugin (audio unit only)
    and call it 'LUFSMeter'. In the Config Tab, Select 'Modules'
    on the left. Select all modules except
    - juce_audio_utils
    - juce_browser_plugin_client.
1.3 For the LUFS Meter, set the 'Module source folder' to
    ./libraries/juce/modules .
1.4 'Set Copying Mode...' to 'Disable local copying for all modules'.
1.5 Select 'XCode (MacOSX) on the left side. The 'Local JUCE folder'
    should be automatically set to '../../libraries/juce/modules'.
    If not, set it.
1.6 In both, XCode Debug and XCode Release choose OSX Base SDK Version =
    "Use Default" and OSX Compatibility Version = "10.4 SDK" for maximum
    backwards compatibility.
1.7 Hit the 'Save Project and Open in XCode...', compile this basic
    plugin and ensure there are no errors. On success, the plugin
    is copied to your local plugin folder
    ~/Library/Audio/Plug-Ins/Components.
1.8 Validate the plugin with::
    auval -64 -v aufx Lufs Klan  (for the 64 bit version)
    auval -v aufx Lufs Klan  (for the 32 bit version)



2. JUCE Basic Plugin as Audio Unit and VST
==========================================

2.1 Download the VST 2.4 SDK (vst_sdk2_4_rev2.zip) by Steinberg.
    Either from
    http://www.steinberg.net/en/company/developer.html
    or from
    http://code.google.com/p/juced/source/browse/trunk/vst/?r=8
2.2 Put the 'pluginterfaces' and the 'public.sdk' folders to
    ./libraries/vstsdk2.4 .
2.3 In the Introducer on the Config Tab, click LUFSMeter on top
    left. Enable the Build VST.
2.4 Click 'XCode (MacOSX)' on the left side. Set the 'VST Folder'
    to '../../libraries/vstsdk2.4'
2.5 Hit the 'Save Project and Open in XCode...', compile this basic
    plugin and ensure there are no errors. On success, the plugin
    is copied to your local plugin folders
    ~/Library/Audio/Plug-Ins/Components
    ~/Library/Audio/Plug-Ins/VST



3. LUFS Meter as Audio Unit and VST
===================================

3.1 Remove the default PluginEditor.* and PluginProcessor.* files and
    replace them with the LUFS Meter files.
3.2 Compile the LUFS meter plugin and ensure there are no errors.



4. Standalone
=============

A default Introjucer GUI application
------------------------------------

4.1 Create a new GUI Application with a basic window using the
    Introjucer. As before, follow 1.3 and 1.4.
    (All modules except juce_audio_plugin_client, juce_audio_utils
    and juce_browser_plugin_client are selected.).
4.3 Give it a try, it should compile.

The default Introjucer plugin as standalone GUI application
-----------------------------------------------------------

4.4 Copy the PluginEditor.* and the PluginProcessor.* from a basic
    plugin project to this projects Source folder and add them in
    the Introjucer.
4.5 This won't compile. You have to manually add the
    'Audio plugin settings..'-section from the AppConfig.h of
    your plugin project to your AppConfig.h of your standalone
    project. Be sure to add it to the USER_CODE_SECTION at the
    top of the AppConfig.h.
    (Actually, only JucePlugin_Name, JucePlugin_MaxNumInputChannels
    and JucePlugin_MaxNumOutputChannels are needed.)
4.6 In there, set JucePlugin_Build_VST and JucePlugin_Build_AU
    to zero.
4.7 Give it a try, it should compile.

 
4.8 Include the juce_audio_utils. (The AudioProcessorPlayer
    is needed by the StandaloneFilterWindow).
4.9 Delete the MainComponent.* files in the Introjucer.
4.10 Modify the Main.cpp and add::
        #include "../../../libraries/juce/modules/juce_audio_plugin_client/Standalone/juce_StandaloneFilterWindow.h"
        ...
        void initialise (const String& commandLine)
        {
            standaloneFilterWindow = new StandaloneFilterWindow(JUCEApplication::getInstance()->getApplicationName(), Colours::lightgrey, nullptr);
            standaloneFilterWindow->setTitleBarButtonsRequired (DocumentWindow::allButtons, false);
            standaloneFilterWindow->setVisible (true);
            standaloneFilterWindow->setResizable (true, true);
        }
        void shutdown()
        {
            standaloneFilterWindow = nullptr; // (deletes our window)
        }
        ...
        private:
            ScopedPointer<StandaloneFilterWindow> standaloneFilterWindow;
 
4.11 Add an additional global function to the PluginProcessor.cpp::
        AudioProcessor* JUCE_CALLTYPE createPluginFilterOfType (AudioProcessor::WrapperType)
        {
            return new DefaultJucePluginAudioProcessor();
        }
     This is called by the StandaloneFilterWindow.
4.12 Give it a try, it should compile.

The LUFS Meter plugin as a standalone GUI application
-----------------------------------------------------

4.13 In the AppConfig.h, set the JucePlugin_MaxNumOutputChannels to 0.
     (To avoid feedback when using a microphone.)
4.14 To be able to use the same source files as the plugin, different
     header files need to be included in the LUFS Meter files. To
     achieve this, a preprocessor definition can be used:
     In the Introjucer go to Config > LUFSMeterStandalone. There
     you'll find the Preprocessor definitions. Add
     ``LUFSMETER_STANDALONE=1`` to it.
4.15 Delete the PluginEditor.* and PluginProcessor.* in the Introducer.
     Add all the files from ../LUFSMeter/Source in the Introducer.
4.16 Apply the changes from 4.11 to the LUFSMeterAudioProcessor.cpp
4.17 Give it a try, it should compile.

