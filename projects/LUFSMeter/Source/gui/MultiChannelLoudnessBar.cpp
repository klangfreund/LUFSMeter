/*
 ===============================================================================
 
 MultiChannelLoudnessBar.cpp
 
 
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
 
 ===============================================================================
 */


#include "MultiChannelLoudnessBar.h"


//==============================================================================
MultiChannelLoudnessBar::MultiChannelLoudnessBar ()
{
}

MultiChannelLoudnessBar::~MultiChannelLoudnessBar ()
{
    loudnessValue.removeListener(this);
}

void MultiChannelLoudnessBar::setValueObjectsToRefereTo (const Value & loudnessValueToReferTo,
                                                         const Value & minLoudnessValueToReferTo,
                                                         const Value & maxLoudnessValueToReferTo)
{
    loudnessValue.referTo(loudnessValueToReferTo);
    loudnessValue.addListener(this);
    
    minLoudness.referTo(minLoudnessValueToReferTo);
    minLoudness.addListener(this);
    maxLoudness.referTo(maxLoudnessValueToReferTo);
    maxLoudness.addListener(this);
    
    determineStretchAndOffset();
}

void MultiChannelLoudnessBar::valueChanged (Value & value)
{
    if (value == loudnessValue)
    {
        repaint();
    }
    else if (value == minLoudness || value == maxLoudness)
    {
        determineStretchAndOffset();
        repaint();
    }
}

//==============================================================================
void MultiChannelLoudnessBar::paint (Graphics& g)
{
    const float width = float (getWidth());
    const float height = float (getHeight());
    
    Array<var>* loudnessArray = loudnessValue.getValue().getArray();
    
//    Array<var> temp;
//    temp.clear();
//    temp.add(-5.0);
//    temp.add(-5.0);
//    loudnessArray = &temp;
    
    if (loudnessArray)
    {
        const int numberOfChannels = loudnessArray->size();
        
        const float widthPerChannel = width / float(numberOfChannels);
        
        // Draw a background
        //    g.setColour(Colours::black);
        //    float x = 0.0f;
        //    float y = 0.0f;
        //    float cornerSize = 3.0f;
        //    g.fillRoundedRectangle(x, y, width, height, cornerSize);
        
        g.setColour(Colours::green);
        for (int k = 0; k != numberOfChannels; ++k)
        {
            //loudnessArray->set(k, -5.0);
            
            // Ensure that the current loudness is in the range ( minLoudness, maxLoudness ) .
            double currentLoudnessOfChannelK = double ((*loudnessArray)[k]);
            currentLoudnessOfChannelK = jmax(currentLoudnessOfChannelK, double (minLoudness.getValue()));
            currentLoudnessOfChannelK = jmin(currentLoudnessOfChannelK, double (maxLoudness.getValue()));
            
            float barHeightInPercent = stretch*currentLoudnessOfChannelK + offset;
            
            float topLeftX = float(k) * widthPerChannel;
            float topLeftY = (1.0f - barHeightInPercent) * height;
            float bottomY = height;
            g.fillRect(topLeftX,
                       topLeftY,
                       widthPerChannel,
                       bottomY-topLeftY);
        }
    }

}

void MultiChannelLoudnessBar::determineStretchAndOffset()
{
    // These two values define a linear mapping
    //    f(x) = stretch * x + offset
    // for which
    //    f(minimumLevel) = 0
    //    f(maximumLevel) = 1
    stretch = 1.0f/(double(maxLoudness.getValue()) - double(minLoudness.getValue()));
    offset = -double(minLoudness.getValue()) * stretch;
}