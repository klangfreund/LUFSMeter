.. author: Samuel Gaehwiler


The JUCE repository inside the LUFS Meter repository
====================================================

How it was set up
-----------------

Not used: Subtree merge strategy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

I wanted to use subtree merging as described in
http://git-scm.com/book/en/Git-Tools-Subtree-Merging .
But this way it's cumbersome to get rid of the JUCE git history.

git subtree
^^^^^^^^^^^

Source:
http://stackoverflow.com/questions/3739393/git-subtree-merge-strategy-possible-without-merging-history

apenwarr's git subtree has been merged into the regular git application.
Ensure that you are working with an up to date version of git.
On the mac you can use homebrew to upgrade.

Get the JUCE repository. Call these on the LUFS Meter root directory::

    git remote add juce git://juce.git.sourceforge.net/gitroot/juce/juce
    git fetch --depth=1 juce

Merge all the LUFS Meter stuff into the master branch.
Put the JUCE files into the libraries folder::

    git subtree add --prefix=libraries --squash juce master
