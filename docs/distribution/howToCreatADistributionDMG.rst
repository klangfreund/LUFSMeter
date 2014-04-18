.. author: Samuel Gaehwiler (klangfreund.com)

How to create a distribution DMG
================================



1. create the dmg
-----------------

- Open 'Disk Utility'
- File -> New -> Blank disk image...
- make it read/write and big enough
- call it something like <finalName>_draft.dmg

2. customize the dmg
--------------------

- Customize the content and the look as you desire.
    - Hint: Command-J -> Always open in icon view
    - Open the terminal to create a shortcut (static link) to e.g. the audio-unit folder:
        ln -s ~/Library/Audio/Plug-Ins/Components/ Components

3. compress the dmg
-------------------

- Open 'Disk Utility'
- Images -> Convert
- Call it something like <finalName>.dmg

4. Add the License (Agreement)
------------------------------

Enter::

    ./licenseDMG.py <finalName>.dmg gpl-2.0.txt

in the Terminal.app
