
****************
LUFSMeter Readme
****************

Files
=====

The *.dll files in this folder are VST2 plugins.
The *.vst3 files in this folder are VST3 plugins.

The multichannel-version is capable of dealing with 1 to 24 channels.
Because some hosts don't handle plugins with a flexible number of input
channels very well, a mono/stereo only version of the LUFSMeter is also
included.


Installation
============

Copy the desired file(s) to the VST plugin folder of your host software.


Troubleshooting
===============

If you work with an earlier version than Windows 7, you might get an error
message claiming that msvcp120.dll is missing.

Solution: Download and install the "Visual C++ Redistributable Packages for
Visual Studio 2013" from http://www.microsoft.com/en-us/download/details.aspx?id=40784 .

Background: The LUFSMeter is developed with the latest toolset from
Microsoft on Windows 7. Like every other application built this way,
on earlier versions of Windows the LUFSMeter needs that additional dll.
