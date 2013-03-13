How to set up a new Juce plugin on OSX
======================================

0 Fix XCode 4.3.2
-----------------

0.1 In XCode: Go to XCode -> 'Open Developer Tool' 
-> 'More Developer Tools...' and download the 'Audio Tools
For XCode'. From the dmg, copy the folder 'CoreAudio' to
/Applications/XCode.app/Contents/Developer/Extras
(You have to create the folder 'Extras').

0.2 Fix the files AUCarbonViewBase.cpp and AUMIDIEffectBase.cpp.
The fixed files are included in this project in the folder
FixedCoreAudioFilesForXCode4.3.2 .


1 Audio Unit
------------

1.1 Get Juce

1.2 Use the Introjucer to set up a audio plugin (audio unit only)
and call it 'LUFSMeter'. Select all modules except
juce_browser_plugin_client.

1.3 Compile this default project and ensure there are no errors.

1.4 Remove the default PluginEditor.* and PluginProcessor.* files and
replace them with the LUFS Meter files. Exclude the files in the
standalone folder.

1.5 Compile the LUFS meter plugin and ensure there are no errors.

2. Standalone
-------------

2.1 Click to top icon on the right (LUFSMeter project icon). Click the big +
button on the buttom called 'Add Target'. Select 'Mac OS X' ->
'Cocoa Application'.
Product name: 'LUFSMeterStandalone'.
Company identifier: 'com.klangfreund'.
Class Prefix: (none)
App Store Category: 'None'.
Create Document-Based Application: false.
Use Core Data: false.
Use Automatic Reference Counting: false (this is a feature for objective-c).
Include Unit Tests: false

NOT
2.2 In the LUFSMeterStandalone folder on the left, delete all files
exept LUFSMeterStandalone-Info.plist and InfoPlist.strings.

2.2 In the LUFSMeterStandalone folder on the left, delete
- main.m
- AppDelegate.h
- AppDelegate.m
- MainMenu.xib

2.3 Create a group 'Source' in the LUFSMeterStandalone folder and drag
and drop all the additional files for the standalone application -
located in the standalone folder on the drive - into it.

2.4 Drag and drop all frameworks (exept the ones in the subfolder
'Other Frameworks') from the group Frameworks to the target
LUFSMeterStandalone -> Build Phases -> Link Binary With Libraries.

2.5 Drag and drop all .cpp files from the group LUFSMeter -> Source 
to the target LUFSMeterStandalone -> Build Phases -> Compile Sources.

2.6 Drag and drop the files that are also used by the plugin from the
group 'Juce Library Code' -> 'Juce AU Wrapper' to the target
LUFSMeterStandalone -> Build Phases -> Compile Sources.
Set the Compiler Flags according to the plugin.

2.7 Drag and drop the files that are also used by the plugin from the
group 'Juce Library Code' to the target
LUFSMeterStandalone -> Build Phases -> Compile Sources.
Set the Compiler Flags according to the plugin.

2.8 In Build Settings, remove the 'Prefix Header' and set 'Precompile
Prefix Header' to 'no'.

2.9 Try to compile. Most likely you need to add some more files
from /Applications/XCode.app/Contents/Developer/Extras/CoreAudio
to 'Juce Library Code'/'Juce AU Wrapper'.

3. VST
------

3.1 Download the VST 2.4 SDK (vst_sdk2_4_rev2.zip) by Steinberg.
Either from
http://www.steinberg.net/en/company/developer.html
or from
http://code.google.com/p/juced/source/browse/trunk/vst/?r=8

3.2 Put the vstsdk2.4 folder anywhere you like and include it in the
target 'LUFSMeter' -> Build Settings -> Header Search Paths .
