.. author: Samuel Gaehwiler


The JUCE repository inside the LUFS Meter repository
====================================================

.. How it was set up
.. -----------------
.. 
.. Not used: Subtree merge strategy
.. ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. 
.. I wanted to use subtree merging as described in
.. http://git-scm.com/book/en/Git-Tools-Subtree-Merging .
.. But this way it's cumbersome to get rid of the JUCE git history.
.. 
.. git subtree
.. ^^^^^^^^^^^
.. 
.. Source:
.. http://stackoverflow.com/questions/3739393/git-subtree-merge-strategy-possible-without-merging-history
.. 
.. apenwarr's git subtree has been merged into the regular git application.
.. Ensure that you are working with an up to date version of git.
.. On the mac you can use homebrew to upgrade.
.. 
.. Get the JUCE repository. Call these on the LUFS Meter root directory::
.. 
..     git remote add juce git://juce.git.sourceforge.net/gitroot/juce/juce
..     git fetch --depth=1 juce
.. 
.. Merge all the LUFS Meter stuff into the master branch.
.. Put the JUCE files into the libraries folder::
.. 
..     git subtree add --prefix=libraries/juce --squash juce/master
.. 
.. Done.

How to update to the latest JUCE version
----------------------------------------

Source:
http://stackoverflow.com/questions/3739393/git-subtree-merge-strategy-possible-without-merging-history

::

    git subtree pull --prefix=libraries/juce --squash juce master    

.. Maybe of interest in the future, if I intend to make my own changes to JUCE:
.. http://www.rawmaterialsoftware.com/viewtopic.php?f=2&t=9730&hilit=subtree#p55782

If there are build errors after the upgrade to the latest JUCE revision, it might
be solved by recreating the XCode project file with the Introjucer.



General git usage
=================


Log tagged commits only
-----------------------

::
    git log --no-walk --tags --decorate

Source: http://stackoverflow.com/questions/21569406/how-does-one-git-log-tagged-commits-only

