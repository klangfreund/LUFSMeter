LUFSMeter
=========

A VST and AudioUnit plugin to measure the loudness, according to EBU R128.

author: Samuel Gaehwiler (www.klangfreund.com)

Official website: http://www.lufsmeter.com


Requirements
------------

The `JUCE framework<http://www.juce.com>`_ is heavily used.
It is already included.

The only thing missing is the VST SDK by Steinberg, since
it's not allowed to redistribute it. Therefore you have to
get it from Steinberg (Search for vst_sdk2_4_rev2.zip at 
http://www.steinberg.net/en/company/developer.html) and copy
the ``pluginterfaces`` and ``public.sdk`` folders into the ``vstsdk2.4``
directory.
