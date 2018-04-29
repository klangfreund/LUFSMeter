/*
 ===============================================================================
 
 SecondOrderIIRFilter.h
 
 
 By Samuel Gaehwiler from Klangfreund.
 Used in the klangfreund.com/lufsmeter/

 License: MIT

 I'd be happy to hear about your usage of this code!
 -> klangfreund.com/contact/
 
 -------------------------------------------------------------------------------
 
 The MIT License (MIT)
 
 Copyright (c) 2018 Klangfreund, Samuel Gaehwiler
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 -------------------------------------------------------------------------------
 
 To release a closed-source product which uses the LUFS Meter or parts of it,
 get in contact via www.klangfreund.com/contact/.
 
 ===============================================================================
 */

#ifndef __FILTER_OF_SECOND_ORDER__
#define __FILTER_OF_SECOND_ORDER__

#include "../MacrosAndJuceHeaders.h"

//==============================================================================
/** A second order IIR (infinite inpulse response) filter.

 The filter will process the signal on every channel like this:
 
 out[k] = b0 * factorForB0[k] + b1 * z1[k] + b2 * z2[k]
 
 with
 factorForB0[k] = in[k] - a1 * z1[k] - a2 * z2[k]
 z1[k] = factorForB0[k-1]
 z2[k] = factorForB0[k-2]
 
 This structure is depicted in ITU-R BS.1770-2 Figure 3 as well as in
 111222_2nd_order_filter_structure.tif .
*/
class SecondOrderIIRFilter
{
public:
    //==============================================================================
    SecondOrderIIRFilter (double b0_at48k_ = 1.0,
                          double b1_at48k_ = 0.0,
                          double b2_at48k_ = 0.0,
                          double a1_at48k_ = 0.0,
                          double a2_at48k_ = 0.0);
    
    virtual ~SecondOrderIIRFilter();

    //==============================================================================
    // Call before the playback starts, to let the filter prepare itself. 
    virtual void prepareToPlay (double sampleRate, int numberOfChannels);
    
    // Call after the playback has stopped, to let the filter free up any 
    // resources it no longer needs. 
    virtual void releaseResources();

    // Renders the next block.
    void processBlock (AudioSampleBuffer& buffer);
    
    void reset();

protected:
    //==============================================================================
    /** Filter coefficients, valid for a sample rate of 48000 Hertz.
     */
    double b0_at48k, b1_at48k, b2_at48k, a1_at48k, a2_at48k;

    /** Filter coefficients for the used sample rate. They are set in
     prepareToPlay.
     */
    double b0, b1, b2, a1, a2;
private:
    /** Filter parameters that are set in the constructor and used in
     prepareToPlay to calculate the filter coefficients.
     */
    double Q, VH, VB, VL, arctanK;

    /** Number of audio channels.
     */
    int numberOfChannels;

    /** Stores the previous value of the variable factorForB2 for every audio channel.
     */
    HeapBlock<double> z1;

    /** Stores the previous value of z1 for every audio channel.
     */
    HeapBlock<double> z2;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SecondOrderIIRFilter);
};

#endif  // __FILTER_OF_SECOND_ORDER__
