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
  (It's the default location for the SDK...)

- If Notepad doesn't break the lines of your textfiles as you have intended,
  use the command::

    :w ++ff=dos /path/to/file.txt

  in VIM. More about it::

    :help 'ff'
    :help ++opt 
  
  (Source: http://vim.1045645.n5.nabble.com/Working-with-windows-line-endings-td1151082.html )
