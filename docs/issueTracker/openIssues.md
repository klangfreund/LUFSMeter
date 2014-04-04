<!--- author: Samuel Gaehwiler (klangfreund.com) !-->


Description of this file
========================

This file is the issue tracker as well as a short term roadmap for the LUFS Meter.
In order of priority.


Open issues / Roadmap
=====================


Reset not working anymore
-------------------------


AU: In Logic, 2 times Mono or 2 times Stereo is shown
-----------------------------------------------------


Don't measure 100ms or 1s based on the expectedRequestRate
----------------------------------------------------------

Use a sample counter! 


Implement some default plugin presets
-------------------------------------

Ensure the LUFS Meter complies to the plugin specifications on Windows and OSX
------------------------------------------------------------------------------

Numeric Gain (Weighting) for each channel user adjustable
---------------------------------------------------------

Part of my answer to an Email at 130204:
To get the accurate LUFS value for 6 channels with my LUFS Meter:
Open an instance of the LUFS-Meter with 5 or 6 input channels.
Ensure that the two surround channels are on channel 4 and 5. Also make sure that the LFE channel is NOT connected at all (e.g. mute this channel, or use a utility plugin where you can pull the gain for this channel).

It's on my todo-list to implement this internally, such that you only have to choose a preset for e.g. 6 channel surround... and off you go.

Rework the GUI
--------------

- Give the plugin an overall look (Skinnable via Look and feel!)
- How to implement the history meter more efficient?
- Settings panel as overlay? Or any other idea such that it's intuitive?

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
