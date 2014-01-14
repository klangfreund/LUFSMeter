/*
 ==============================================================================
 
 LoudnessHistoryGroup.cpp
 
 Created: 13 Jan 2014 11:13:44pm
 Author:  Samuel Gaehwiler
 
 This file is part of the LUFS Meter audio measurement plugin.
 Copyright 2011-12 by Klangfreund, Samuel Gaehwiler.
 
 -------------------------------------------------------------------------------
 
 The LUFS Meter can be redistributed and/or modified under the terms of the GNU
 General Public License Version 2, as published by the Free Software Foundation.
 A copy of the license is included with these source files. It can also be found
 at www.gnu.org/licenses.
 
 The LUFS Meter is distributed WITHOUT ANY WARRANTY.
 See the GNU General Public License for more details.
 
 -------------------------------------------------------------------------------
 
 To release a closed-source product which uses the LUFS Meter or parts of it,
 a commercial license is available. Visit www.klangfreund.com/lufsmeter for more
 information.
 
 ==============================================================================
 */

#include "LoudnessHistoryGroup.h"

LoudnessHistoryGroup::LoudnessHistoryGroup ()
{
}

LoudnessHistoryGroup::~LoudnessHistoryGroup ()
{
}

void LoudnessHistoryGroup::timerCallback ()
{
}

void LoudnessHistoryGroup::resized ()
{
    // Resize all children to the size of this (parent) component.
    for (int childIndex = 0; childIndex < getNumChildComponents(); ++childIndex)
    {
        Component* child = getChildComponent (childIndex);
        child->setBounds(0, 0, getWidth(), getHeight());
    }
}

void LoudnessHistoryGroup::paint (juce::Graphics &g)
{
    // Children get automatically repainted, when this is called.
}