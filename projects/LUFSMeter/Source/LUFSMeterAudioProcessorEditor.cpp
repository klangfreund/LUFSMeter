/*
 ===============================================================================
 
 LUFSMeterAudioProcessorEditor.cpp
 
 
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


#include "LUFSMeterAudioProcessor.h"
#include "LUFSMeterAudioProcessorEditor.h"


//==============================================================================
LUFSMeterAudioProcessorEditor::LUFSMeterAudioProcessorEditor (LUFSMeterAudioProcessor* ownerFilter)
  : AudioProcessorEditor (ownerFilter),
    momentaryLoudnessValue (var(-300.0)),
    momentaryLoudnessValues (),
    shortTermLoudnessValue (var(-300.0)),
    integratedLoudnessValue (var(-300.0)),
    distanceBetweenLevelBarAndTop (10),
    distanceBetweenLevelBarAndBottom (32),
    backgroundGridCaption (distanceBetweenLevelBarAndTop, distanceBetweenLevelBarAndBottom, getProcessor()->loudnessBarMinValue, getProcessor()->loudnessBarMaxValue),
    momentaryLoudnessBar (),
    shortTermLoudnessBar (shortTermLoudnessValue, getProcessor()->loudnessBarMinValue, getProcessor()->loudnessBarMaxValue),
    integratedLoudnessBar (integratedLoudnessValue, getProcessor()->loudnessBarMinValue, getProcessor()->loudnessBarMaxValue),
    momentaryLoudnessCaption (String::empty, "M"),
    shortTermLoudnessCaption (String::empty, "S"),
    integratedLoudnessCaption (String::empty, "I"),
    loudnessHistory (integratedLoudnessValue, getProcessor()->loudnessBarMinValue, getProcessor()->loudnessBarMaxValue),
    preferencesPaneVisible (false),
    preferencesPaneXPosition (-380),
    preferencesPaneYPosition(50),
    preferencesPaneWidth (400),
    preferencesPaneHeight(300)
{
    momentaryLoudnessBar.setValueObjectsToRefereTo (momentaryLoudnessValues,
                                                    getProcessor()->loudnessBarMinValue, 
                                                    getProcessor()->loudnessBarMaxValue);
    
    // Add the background
    addAndMakeVisible (&backgroundGrid);
    addAndMakeVisible (&backgroundGridCaption);
    addAndMakeVisible(&backgroundVerticalLinesAndCaption);
    
    // TEMP:
    // Add a label that will display the current timecode and status..
//    addAndMakeVisible (&infoLabel);
//    infoLabel.setColour (Label::textColourId, Colours::green);
    
    // Add the meter bars
    addAndMakeVisible (&momentaryLoudnessBar);    
    addAndMakeVisible (&shortTermLoudnessBar);
    addAndMakeVisible (&integratedLoudnessBar);
    
    // Add the numeric values
    addAndMakeVisible (&momentaryLoudnessNumeric);
    momentaryLoudnessNumeric.getLevelValueObject().referTo(momentaryLoudnessValue);
    addAndMakeVisible (&shortTermLoudnessNumeric);
    shortTermLoudnessNumeric.getLevelValueObject().referTo(shortTermLoudnessValue);
    addAndMakeVisible (&integratedLoudnessNumeric);
    integratedLoudnessNumeric.getLevelValueObject().referTo(integratedLoudnessValue);
    
    // Add the captions
    const int fontHeight = 16;
    const Font fontForCaptions (fontHeight);
    const Justification justification (Justification::horizontallyCentred);
    momentaryLoudnessCaption.setFont(fontForCaptions);
    momentaryLoudnessCaption.setColour (Label::textColourId, Colours::green);
    // momentaryLoudnessCaption.setColour (Label::backgroundColourId, Colours::red);
    momentaryLoudnessCaption.setJustificationType(justification);
    addAndMakeVisible (&momentaryLoudnessCaption);
    shortTermLoudnessCaption.setFont(fontForCaptions);
    shortTermLoudnessCaption.setColour (Label::textColourId, Colours::green);
    shortTermLoudnessCaption.setJustificationType(justification);
    addAndMakeVisible (&shortTermLoudnessCaption);
    integratedLoudnessCaption.setFont(fontForCaptions);
    integratedLoudnessCaption.setColour (Label::textColourId, Colours::green);
    integratedLoudnessCaption.setJustificationType(justification);
    addAndMakeVisible (&integratedLoudnessCaption);
    
    // Add the level history graph.
    addAndMakeVisible (&loudnessHistory);
    
    // Add the reset button
    resetButton.addListener(this);
    resetButton.setButtonText("reset");
    resetButton.setColour(TextButton::buttonColourId, Colours::green);
    addAndMakeVisible (&resetButton);
    
    // Add the preferences pane
    preferencesPane.showOrHidePreferences.addListener(this);
    preferencesPane.loudnessBarSize.addListener(this);
    preferencesPane.loudnessBarSize.setRange(5.0, 300.0, 1);
    preferencesPane.loudnessBarSize.setValue(getProcessor()->loudnessBarWidth);
    preferencesPane.loudnessBarRange.addListener(this);
    preferencesPane.loudnessBarRange.setRange(-100, 0.0, 1);
    preferencesPane.loudnessBarRange.getMinValueObject().referTo(getProcessor()->loudnessBarMinValue);
    preferencesPane.loudnessBarRange.getMaxValueObject().referTo(getProcessor()->loudnessBarMaxValue);
    addAndMakeVisible(&preferencesPane);

    
    // Add the triangular resizer component for the bottom-right of the UI.
    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    
    resizeLimits.setSizeLimits (150, 150, 800, 400);
    
    // Set our component's initial size to be the last one that was stored in 
    // the filter's settings.
    setSize (ownerFilter->lastUIWidth,
             ownerFilter->lastUIHeight);
    
    loudnessHistory.reset();
    
    // Start the timer which will refresh the GUI elements.
    const int refreshIntervalInMilliseconds = 50;
    startTimer (refreshIntervalInMilliseconds);
}

LUFSMeterAudioProcessorEditor::~LUFSMeterAudioProcessorEditor()
{
//    momentaryLoudnessValue.removeListener(&momentaryLoudnessBar);
//    shortTermLoudnessValue.removeListener(&shortTermLoudnessBar);
//    integratedLoudnessValue.removeListener(&integratedLoudnessBar);
}

//==============================================================================
void LUFSMeterAudioProcessorEditor::paint (Graphics& g)
{
    // Draw the background
    g.fillAll(Colours::black);
}

void LUFSMeterAudioProcessorEditor::resized()
{
    // DEB("Height of main component = " + String(getHeight()))

    const int levelBarWidth = jmax( getProcessor()->loudnessBarWidth, 5);
    const int spaceBetweenBars = jmin(levelBarWidth/5, 10); // This distance is 
        // also used for the border on the right side.
    const int heightOfNumericValues = levelBarWidth/3;
    const int heightOfLoudnessCaptions = heightOfNumericValues;
    distanceBetweenLevelBarAndBottom = heightOfNumericValues + heightOfLoudnessCaptions;
    const int levelBarBottomPosition = getHeight() - distanceBetweenLevelBarAndBottom;
    const int levelBarNumericTopPosition = getHeight() - distanceBetweenLevelBarAndBottom;
    const int levelBarCaptionTopPosition = getHeight() - heightOfLoudnessCaptions;
    
    const int backgroundGridCaptionWidth = 35;
    
    // Font for the loudnessCaptions
    const int fontHeight = heightOfLoudnessCaptions;
    const Font fontForCaptions (fontHeight);
    
    backgroundGrid.setBounds(0,
                             distanceBetweenLevelBarAndTop,
                             getWidth(),
                             levelBarBottomPosition - distanceBetweenLevelBarAndTop);
    
    const int momentaryLoudnessBarX = getWidth() - spaceBetweenBars - levelBarWidth;
    momentaryLoudnessBar.setBounds(momentaryLoudnessBarX,
                                   distanceBetweenLevelBarAndTop,
                                   levelBarWidth,
                                   levelBarBottomPosition - distanceBetweenLevelBarAndTop);
    momentaryLoudnessNumeric.setBounds (momentaryLoudnessBarX,
                                        levelBarNumericTopPosition,
                                        levelBarWidth,
                                        heightOfNumericValues);
    momentaryLoudnessCaption.setBounds(momentaryLoudnessBarX,
                                       levelBarCaptionTopPosition,
                                       levelBarWidth,
                                       heightOfLoudnessCaptions);
    momentaryLoudnessCaption.setFont(fontForCaptions);
    
    const int shortTermLoudnessBarX = momentaryLoudnessBarX - spaceBetweenBars - levelBarWidth;
    shortTermLoudnessBar.setBounds(shortTermLoudnessBarX,
                                   distanceBetweenLevelBarAndTop,
                                   levelBarWidth,
                                   levelBarBottomPosition - distanceBetweenLevelBarAndTop);
    shortTermLoudnessNumeric.setBounds (shortTermLoudnessBarX,
                                        levelBarNumericTopPosition,
                                        levelBarWidth,
                                        heightOfNumericValues);
    shortTermLoudnessCaption.setBounds(shortTermLoudnessBarX,
                                       levelBarCaptionTopPosition,
                                       levelBarWidth,
                                       heightOfLoudnessCaptions);
    shortTermLoudnessCaption.setFont(fontForCaptions);
    
    const int integratedLoudnessBarX = shortTermLoudnessBarX - spaceBetweenBars - levelBarWidth;
    integratedLoudnessBar.setBounds(integratedLoudnessBarX, 
                                    distanceBetweenLevelBarAndTop, 
                                    levelBarWidth, 
                                    levelBarBottomPosition - distanceBetweenLevelBarAndTop);
    integratedLoudnessNumeric.setBounds (integratedLoudnessBarX,
                                         levelBarNumericTopPosition,
                                         levelBarWidth,
                                         heightOfNumericValues);
    integratedLoudnessCaption.setBounds(integratedLoudnessBarX,
                                        levelBarCaptionTopPosition,
                                        levelBarWidth,
                                        heightOfLoudnessCaptions);
    integratedLoudnessCaption.setFont(fontForCaptions);
    
    const int backgroundGridCaptionX = integratedLoudnessBarX - spaceBetweenBars - backgroundGridCaptionWidth;
    backgroundGridCaption.setBounds(backgroundGridCaptionX, 0, backgroundGridCaptionWidth, levelBarBottomPosition + 32);

    backgroundVerticalLinesAndCaption.setBounds(0, distanceBetweenLevelBarAndTop, jmax(backgroundGridCaptionX, 0), levelBarBottomPosition + 32 - distanceBetweenLevelBarAndTop);
    loudnessHistory.setBounds(0, distanceBetweenLevelBarAndTop, jmax(backgroundGridCaptionX, 0), levelBarBottomPosition - distanceBetweenLevelBarAndTop);
    
//    const bool broadcastChangeMessage = false;
//    momentaryLoudnessCaption.setText("M", broadcastChangeMessage);

    // TEMP
    infoLabel.setBounds (10, 4, 380, 25);
    
//    resetButton.setBounds(10, getHeight()-35, 80, 25);
    resetButton.setBounds(25, 12, 80, 25);
    
    preferencesPane.setBounds(preferencesPaneXPosition,
                              preferencesPaneYPosition,
                              preferencesPaneWidth,
                              preferencesPaneHeight);
    
    resizer->setBounds (getWidth() - 16, getHeight() - 16, 16, 16);
    
    getProcessor()->lastUIWidth = getWidth();
    getProcessor()->lastUIHeight = getHeight();
}

LUFSMeterAudioProcessor* LUFSMeterAudioProcessorEditor::getProcessor() const
{
    return static_cast <LUFSMeterAudioProcessor*> (getAudioProcessor());
}

// quick-and-dirty function to format a timecode string
static const String timeToTimecodeString (const double seconds)
{
    const double absSecs = fabs (seconds);
    
    const int hours = (int) (absSecs / (60.0 * 60.0));
    const int mins  = ((int) (absSecs / 60.0)) % 60;
    const int secs  = ((int) absSecs) % 60;
    
    String s;
    if (seconds < 0)
        s = "-";
    
    s << String (hours).paddedLeft ('0', 2) << ":"
    << String (mins).paddedLeft ('0', 2) << ":"
    << String (secs).paddedLeft ('0', 2) << ":"
    << String (roundToInt (absSecs * 1000) % 1000).paddedLeft ('0', 3);
    
    return s;
}

// quick-and-dirty function to format a bars/beats string
static const String ppqToBarsBeatsString (double ppq, double /*lastBarPPQ*/, int numerator, int denominator)
{
    if (numerator == 0 || denominator == 0)
        return "1|1|0";
    
    const int ppqPerBar = (numerator * 4 / denominator);
    const double beats  = (fmod (ppq, ppqPerBar) / ppqPerBar) * numerator;
    
    const int bar    = ((int) ppq) / ppqPerBar + 1;
    const int beat   = ((int) beats) + 1;
    const int ticks  = ((int) (fmod (beats, 1.0) * 960.0));
    
    String s;
    s << bar << '|' << beat << '|' << ticks;
    return s;
}

// Updates the text in our position label.
void LUFSMeterAudioProcessorEditor::displayPositionInfo (const AudioPlayHead::CurrentPositionInfo& pos)
{
    lastDisplayedPosition = pos;
    String displayText;
    displayText.preallocateBytes (128);
    
    displayText << String (pos.bpm, 2) << " bpm, "
    << pos.timeSigNumerator << '/' << pos.timeSigDenominator
    << "  -  " << timeToTimecodeString (pos.timeInSeconds);
//    << "  -  " << ppqToBarsBeatsString (pos.ppqPosition, pos.ppqPositionOfLastBarStart,
//                                        pos.timeSigNumerator, pos.timeSigDenominator);
    
    if (pos.isRecording)
        displayText << "  (recording)";
    else if (pos.isPlaying)
        displayText << "  (playing)";
    
    infoLabel.setText (displayText, false);
}

// This timer periodically updates the labels.
void LUFSMeterAudioProcessorEditor::timerCallback()
{
    AudioPlayHead::CurrentPositionInfo newPos (getProcessor()->lastPosInfo);
    
    if (lastDisplayedPosition != newPos)
        displayPositionInfo (newPos);
    
    float momentaryLoudnessOfFirstChannel = (getProcessor()->getMomentaryLoudness()).getFirst();
    jassert(momentaryLoudnessOfFirstChannel > -400)
    momentaryLoudnessValue.setValue(momentaryLoudnessOfFirstChannel);
    
    // momentary loudness values
    // -------------------------
    // source:
    const Array<float>& momentaryLoudnessFromEbu128LM = getProcessor()->getMomentaryLoudness();
    // destination:
    Array<var> momentaryLoudness;
    
    
    for (int k = 0; k != momentaryLoudnessFromEbu128LM.size() ; ++k)
    {
        double momentaryLoudnessOfTheKthChannel = double (momentaryLoudnessFromEbu128LM[k]);
        momentaryLoudness.add (momentaryLoudnessOfTheKthChannel);
    }
    //momentaryLoudnessValues.setValue (var (momentaryLoudness));
    
    float shortTermLoudness = getProcessor()->getShortTermLoudness();
    jassert(shortTermLoudness > -400)
    shortTermLoudnessValue.setValue(shortTermLoudness);

    float integratedLoudness = getProcessor()->getIntegratedLoudness();
    jassert(integratedLoudness > -400)
    integratedLoudnessValue.setValue(integratedLoudness);
}

void LUFSMeterAudioProcessorEditor::buttonClicked(Button* button)
{
    if (button == &resetButton)
    {
        getProcessor()->reset();
        loudnessHistory.reset();
    }
    else if (button == &(preferencesPane.showOrHidePreferences))
    {
        if (!preferencesPaneVisible)
        {
            preferencesPaneXPosition = 0;
            preferencesPaneVisible = true;
        }
        else
        {
            preferencesPaneXPosition = -380;
            preferencesPaneVisible = false;
        }
        
        ComponentAnimator& animator = Desktop::getInstance().getAnimator();
        
        const Rectangle<int> finalBounds = Rectangle<int>(preferencesPaneXPosition,
                                                          preferencesPaneYPosition,
                                                          preferencesPaneWidth,
                                                          preferencesPaneHeight);
        const float finalAlpha = 0.5f;
        const int animationDurationMilliseconds = 300;
        const bool useProxyComponent = false;
        const double startSpeed = 0.0;
        const double endSpeed = 0.0;
        animator.animateComponent(&preferencesPane, finalBounds, finalAlpha, animationDurationMilliseconds, useProxyComponent , startSpeed, endSpeed);
    }
}

void LUFSMeterAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &(preferencesPane.loudnessBarSize))
    {
        // Set the value in the LUFSMeterAudioProcessor instance
        getProcessor()->loudnessBarWidth = preferencesPane.loudnessBarSize.getValue();
        
        // Update the GUI
        resized();
    }
    else if (slider == &(preferencesPane.loudnessBarRange))
    {
        // Set the value in the LUFSMeterAudioProcessor instance
        getProcessor()->loudnessBarMinValue = preferencesPane.loudnessBarRange.getMinValue();
        getProcessor()->loudnessBarMaxValue = preferencesPane.loudnessBarRange.getMaxValue();
        
        // Update the GUI
        resized();
    }
}
