********************************
How to set up Windows 7 for JUCE
********************************


Download and install Microsoft's development tools
==================================================

Windows 7 (64 bit)
------------------

Ensure that you have the 64 bit version installed.
To check:
Start -> Control Panel -> System -> System Type: 64-bit OS

How to stay up to date
^^^^^^^^^^^^^^^^^^^^^^

The first time, this might take quite some time! (>2h)

Start -> All Programs -> Windows Update

Visual C++ 2010 Express
-----------------------

http://www.microsoft.com/visualstudio/en-us/products/2010-editions/visual-cpp-express


Windows SDK v7.1
----------------

NOT NEEDED IN VS 2013 anymore

Because Visual C++ only ships with a 32 bit C++ compiler. Here, a
64 bit C++ compiler is included.

(source: http://stackoverflow.com/questions/1865069/how-to-compile-a-64-bit-application-using-visual-c-2010-express )


JUCE
====

make file extensions visible
----------------------------

Ensure that file extensions are shown in Windows:
In
Start -> Control Panel -> Folder Options -> View
uncheck the "Hide extensions for known file types".

Don't work on a virtual box shared folder, copy the files over to the
local drive of your virtual (or real) machine.

JuceDemo
--------

Open juce/extras/JuceDemo/Builds/VisualStudio2010/"Juce Demo.sln"
with Visual C++ Express 2010 and press F5 (or Debug -> "Start Debugging")

It should work out of the box. (Thank you so much, Jules!)

LUFS Meter
----------

For VS2013, be sure to set the Platform Toolset to v120_xp in the Introjucer ->
Visual Studio 2013 Settings. This guarantees backwards compatibility back to XP.

Open LUFSMeter.sln .
Go to Project -> LUFSMeter Properties... 
Choose "All Configurations" on the dropdown menu on the top left.

Configuration Properties
-> C/C++ -> General
and edit the "Additional Include Directories"
Change "c:\SDKs\vstsdk2.4" to "..\..\vstsdk2.4"
Press F7 (or Debug -> "Build Solution")

The compiled vst dll is located at

LUFSMeter\Builds\VisualStudio2010\Debug

Copy it (32bit dll) to

C:\Program Files (x86)\Steinberg\VSTPlugins


Microsoft Visual C++ 2010 Express Hints
=======================================

Error List
----------

To view the error list after a compile failure:

View -> "Other Windows" -> "Error List"

Release build
-------------
 
.. Select
.. Tools -> Settings -> Expert Settings
.. 
.. This enables the "Build" Menu.

To compile for release:
Choose "Release" in the Solutions Configuration Dropdown menu.
(If not done correctly, you have to set the vstsdk2.4 folder again - see above.)
Build (F7).


64 bit
======

( source: http://stackoverflow.com/questions/1865069/how-to-compile-a-64-bit-application-using-visual-c-2010-express )

Go to Project -> LUFSMeter Properties... 
Choose "All Configurations" on the dropdown menu on the top left.

On the top right, press the "Configuration Manager..."

Find your project, hit the Platform drop-down, select New, then select x64.

Now change the "Active solution platform" drop-down menu to "x64." When you return to the Properties dialog box, the "Platform" drop-down should now read "x64."

Finally, change your toolset. In the Properties menu of your project, under Configuration Properties | General, change Platform Toolset from "v100" to "Windows7.1SDK".


Installer
=========

Use WinRAR (Commands -> Add files to archive) and create a selfextracting (SFX) exe with a license agreement window (Add comment).

other options
http://stackoverflow.com/questions/3767/what-is-the-best-choice-for-building-windows-installers,
http://www.kvraudio.com/forum/printview.php?t=329873&start=0


