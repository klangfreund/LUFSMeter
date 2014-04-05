.. author: Samuel Gaehwiler (klangfreund.com)

**********************************
How to deploy the release versions
**********************************

Mac OSX
=======

- In XCode (5.0.2) ensure, that Architectures = Universal (32/64-bit Intel) is
  selected.

- Product -> Archive

- Once finished, the Organizer will present you the newly generated archive.
  Click the "Distribute..." button.
  Select "Save Built Products" and choose a location to store it.

- The component-File IS the audio unit plugin.

- Copy this file and change the file extension to vst. Now you also have the
  VST plugin.


Windows 7
=========

- Copy the Steinberg VST SDK 2.4 to the folder c:\SDKs\vstsdk2.4 .
  (It's the default location for the SDK... just do it)
