LUFSMeter open issues
*********************

.. author: Samuel Gaehwiler (klangfreund.com)


Open issues / Roadmap
=====================

BUG: The font is all messed up in OSX 10.6
------------------------------------------

Description: At the moment, the font is not specified i.e. it uses the JUCE default one.
-> Use the example plugin to demonstrate the issue.

Comments: Since I work on 10.9 I can't directly test this. Instead I have installed OSX 10.6
on a virtual machine. But I couldn't see any issue at all, neither in 10.6 nor in 10.6.8.


Don't measure 100ms or 1s based on the expectedRequestRate !!!
--------------------------------------------------------------

Use a sample counter!


Implement preset handling
-------------------------

Top row: Preset dropdown and a preset save button.

Loading is done as soon as a preset is selected from the drop down.

If the save button is pressed, a (non modal) dialog will appear:
1: Save as new preset?
2: Overwrite the current preset?
3: Save as startup (default) setting?

After 1 or 2 is pressed: Choose a preset name and a description (for the tooltip).


Rework the Preferences pane
---------------------------

Tabs below the preset stuff.
With the following tabs:
- Scales
- Look (including size, colours and history graph settings)
- Weighting (only Pro)

Rename Preferences to Settings?


Extensive tooltip for every setting
-----------------------------------

Add a "?" button to turn in on and off.
Tooltips should appear immediately.


Implement some default plugin presets
-------------------------------------


User-adjustable colours
-----------------------
 

Numeric Gain (Weighting) for each channel user adjustable (pro)
---------------------------------------------------------------

Part of my answer to an Email at 130204:
To get the accurate LUFS value for 6 channels with my LUFS Meter:
Open an instance of the LUFS-Meter with 5 or 6 input channels.
Ensure that the two surround channels are on channel 4 and 5. Also make sure that the LFE channel is NOT connected at all (e.g. mute this channel, or use a utility plugin where you can pull the gain for this channel).

It's on my todo-list to implement this internally, such that you only have to choose a preset for e.g. 6 channel surround... and off you go.


Transport control
-----------------

Add a toggle to the preferences pane: Enable transport control.
-> Automatically reset if the playhead is moved.
-> Pause the measurement when stopped and show a pause symbol in the middle of the plugin.
-> Continue measurement when play is engaged again in the DAW.

Instead of "reset" make a toggle button "start" and "stop".
Make it automatable.


The LRA measurement is not accurate
-----------------------------------

The EBU test files come in handy here.


Ensure the LUFS Meter complies to the plugin specifications on Windows and OSX
------------------------------------------------------------------------------



BUG: If an instance of the two channel and the multichannel LUFSMeter is loaded, one of them doesn't work
---------------------------------------------------------------------------------------------------------

Host: Logic X

As soon as the working one is removed, the non-working one starts to operate.


Gain Fader on the right (pro)
-----------------------------

Which can be set automatically after an analysis.


True Peak Measurement (pro)
---------------------------

Implement True Peak Measurement.


Rework the GUI
--------------

- How to implement the history meter more efficient?
- Settings panel as overlay? Or any other idea such that it's more intuitive?

Website: Improve usability, add a klangfreund.com index page and add a getting started tutorial
-----------------------------------------------------------------------------------------------

Embedded fonts:
https://news.ycombinator.com/item?id=7406287
https://github.com/alfredxing/brick
https://developer.mozilla.org/en-US/docs/Web/CSS/@font-face


Website: Implement a notification function for interested customers
-------------------------------------------------------------------

- Email Newsletter?
- RSS Feed?
- Twitter or Facebook?

Linux
-----

- Compile the LUFS Meter for Linux


general improvements
====================

general
=======

also try to use a ringbuffer instead of the accumulators and measure the efficiency.


vu meter
========

(source: http://www.rawmaterialsoftware.com/viewtopic.php?f=2&t=297&hilit=meter)

    - Have you made sure that your meter components are opaque? If they're not, then all their parent components will have to get repainted every time, which can create enormous overheads. Check out the setOpaque() method in Component. 

    - Also, to speed them up in tracktion I keep an image buffered and just draw that each time rather than rendering the colour gradients. 

    - And obviously only paint the smallest bit that's changed - to help with debugging all this, try turning on the JUCE_ENABLE_REPAINT_DEBUGGING flag in juce_Config.h, which will draw little coloured rectangles around the bits that get drawn, so you can see what's going on.

source: http://www.rawmaterialsoftware.com/viewtopic.php?f=2&t=611&hilit=meter :

    - Your setValue() method has to be smarter, and call repaint() for only the smallest rectangle that will have changed by the change in value - so if your bar moves up one pixel, just repaint that bit. If it's a needle, call repaint for only the smallest rectangle that holds the new needle position.


Look and feel:
http://www.rawmaterialsoftware.com/viewtopic.php?f=2&t=8368&hilit=lookandfeel


About
=====

This file is the issue tracker as well as a short term roadmap for the LUFS Meter.
The issues are listed in order of priority.
