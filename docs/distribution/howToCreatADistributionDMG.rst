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

- Customize the content and look to your liking.
    - Hint: Command-J -> Always open in icon view

3. compress the dmg
-------------------

- Open 'Disk Utility'
- Images -> Convert
- Call it something like <finalName>.dmg

4. Add the License (Agreement)
------------------------------

Enter::

    ./licenseDMGmodified.py <finalName>.dmg gpl-2.0.txt

in the Terminal.app
