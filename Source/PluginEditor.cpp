/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Distortion.h"
#include "Oscilloscope.h"
#include <string>
#include "Parameters.h"

//==============================================================================
DistAdvAudioProcessorEditor::DistAdvAudioProcessorEditor
(DistAdvAudioProcessor& p)
    : juce::AudioProcessorEditor(&p), audioProcessor(p), scopeComponent(audioProcessor.getAudioBufferQueue())
{
    setSize(700, 700);
    addAndMakeVisible(scopeComponent);




    /*
        juce::Slider ngPreThreshSlider;
    juce::Slider ngPreRatioSlider;
    juce::Slider ngPreAtkSlider;
    juce::Slider ngPreRelSlider;

    juce::Slider ngPostThreshSlider;
    juce::Slider ngPostRatioSlider;
    juce::Slider ngPostAtkSlider;
    juce::Slider ngPostRelSlider;
*/


    //ng1 - pre
    ngPreThreshSlider.setSliderStyle(juce::Slider::Rotary);
    ngPreThreshSlider.setRange(-30.0f, 30.0f, 1.0f);
    ngPreThreshSlider.setValue(-30.0f);
    ngPreThreshSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    ngPreThreshSlider.addListener(this);
    addAndMakeVisible(ngPreThreshSlider);

    ngPreRatioSlider.setSliderStyle(juce::Slider::Rotary);
    ngPreRatioSlider.setRange(1.0f, 10.0f, 1.0f);
    ngPreRatioSlider.setValue(1.0f);
    ngPreRatioSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    ngPreRatioSlider.addListener(this);
    addAndMakeVisible(ngPreRatioSlider);

    ngPreAtkSlider.setSliderStyle(juce::Slider::Rotary);
    ngPreAtkSlider.setRange(5.0f, 1000.0f, 5.0f);
    ngPreAtkSlider.setValue(50.0f);
    ngPreAtkSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    ngPreAtkSlider.addListener(this);
    addAndMakeVisible(ngPreAtkSlider);

    ngPreRelSlider.setSliderStyle(juce::Slider::Rotary);
    ngPreRelSlider.setRange(5.0f, 1000.0f, 5.0f);
    ngPreRelSlider.setValue(50.0f);
    ngPreRelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    ngPreRelSlider.addListener(this);
    addAndMakeVisible(ngPreRelSlider);

    //

    //ng2 - post
    ngPostThreshSlider.setSliderStyle(juce::Slider::Rotary);
    ngPostThreshSlider.setRange(-30.0f, 30.0f, 1.0f);
    ngPostThreshSlider.setValue(-30.0f);
    ngPostThreshSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    ngPostThreshSlider.addListener(this);
    addAndMakeVisible(ngPostThreshSlider);

    ngPostRatioSlider.setSliderStyle(juce::Slider::Rotary);
    ngPostRatioSlider.setRange(0.0f, 10.0f, 1.0f);
    ngPostRatioSlider.setValue(1.0f);
    ngPostRatioSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    ngPostRatioSlider.addListener(this);
    addAndMakeVisible(ngPostRatioSlider);

    ngPostAtkSlider.setSliderStyle(juce::Slider::Rotary);
    ngPostAtkSlider.setRange(5.0f, 2000.0f, 5.0f);
    ngPostAtkSlider.setValue(5.0f);
    ngPostAtkSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    ngPostAtkSlider.addListener(this);
    addAndMakeVisible(ngPostAtkSlider);

    ngPostRelSlider.setSliderStyle(juce::Slider::Rotary);
    ngPostRelSlider.setRange(5.0f, 2000.0f, 5.0f);
    ngPostRelSlider.setValue(50.0f);
    ngPostRelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    ngPostRelSlider.addListener(this);
    addAndMakeVisible(ngPostRelSlider);


    //end gates
    lowpassInSlider.setSliderStyle(juce::Slider::Rotary);
    lowpassInSlider.setRange(20.0f, 666.0f);
    lowpassInSlider.setValue(20.0f);
    lowpassInSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    lowpassInSlider.addListener(this);
    addAndMakeVisible(lowpassInSlider);


    gainKnob.setSliderStyle(juce::Slider::Rotary);
    gainKnob.setRange(1.0f, 11.0f);
    gainKnob.setValue(2.0f);
    gainKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    gainKnob.addListener(this);
    addAndMakeVisible(gainKnob);




    distSelect.addItem("EGGIE", 1); //hc1
    distSelect.addItem("SWEETPEA", 4); //hc2
    distSelect.addItem("DANDY", 2);
    distSelect.addItem("DAISY", 3);
    distSelect.addItem("SPENCER1", 5);
    distSelect.addItem("SPENCER2", 6);
    distSelect.addItem("SPENCER3", 7);
    distSelect.setSelectedId(1);
    distSelect.addListener(this);
    addAndMakeVisible(distSelect);

    driveSlider.setRange(0.0f, 80.0f);
    driveSlider.setValue(1.0f);
    driveSlider.addListener(this);
    addAndMakeVisible(driveSlider);

    ceilingSlider.setRange(0.0f, 1.0f);
    ceilingSlider.setValue(1.f);
    ceilingSlider.addListener(this);
    addAndMakeVisible(ceilingSlider);

    mixSlider.setRange(0.0f, 1.0f);
    mixSlider.setValue(1.f);
    mixSlider.addListener(this);
    addAndMakeVisible(mixSlider);

    threshSlider.setRange(0.0f, 1.0f);
    threshSlider.setValue(1.0f);
    threshSlider.addListener(this);
    addAndMakeVisible(threshSlider);

    reverbWidthSlider.setRange(0.0f, 1.0f);
    reverbWidthSlider.setValue(0.0f);
    reverbWidthSlider.addListener(this);
    addAndMakeVisible(reverbWidthSlider);

    reverbDryLevel.setRange(0.0f, 1.0f);
    reverbDryLevel.setValue(1.0f);
    reverbDryLevel.addListener(this);
    addAndMakeVisible(reverbDryLevel);

    reverbWetLevel.setRange(0.0f, 1.0f);
    reverbWetLevel.setValue(0.5f);
    reverbWetLevel.addListener(this);
    addAndMakeVisible(reverbWetLevel);


    reverbDampingSlider.setRange(0.0f, 1.0f);
    reverbDampingSlider.setValue(0.0f);
    reverbDampingSlider.addListener(this);
    addAndMakeVisible(reverbDampingSlider);

    reverbRoomSizeSlider.setRange(0.0f, 1.0f);
    reverbRoomSizeSlider.setValue(0.0f);
    reverbRoomSizeSlider.addListener(this);
    addAndMakeVisible(reverbRoomSizeSlider);


    tubeMix.setRange(0.0f, 1.0f,.1f);
    tubeMix.setValue(0.0f);
    tubeMix.addListener(this);
    addAndMakeVisible(tubeMix);

    tubeIG.setRange(0.0f, 2.0f, .1f);
    tubeIG.setValue(0.0f);
    tubeIG.addListener(this);
    addAndMakeVisible(tubeIG);

    tubeOG.setRange(0.0f, 5.0f);
    tubeOG.setValue(5.0f);
    tubeOG.addListener(this);
    addAndMakeVisible(tubeOG);

    tubeBias.setRange(0.0f, 3.0f);
    tubeBias.setValue(0.5f);
    tubeBias.addListener(this);
    addAndMakeVisible(tubeBias);

    tubeDrive.setRange(0.0f, 5.0f);
    tubeDrive.setValue(1.0f);
    tubeDrive.addListener(this);
    addAndMakeVisible(tubeDrive);

    delayTime.setRange(0.0f, 3000.0f);
    delayTime.setValue(1.0f);
    delayTime.addListener(this);
    addAndMakeVisible(delayTime);


    delayFeedback.setRange(0.0f, 100.0f);
    delayFeedback.setValue(1.0f);
    delayFeedback.addListener(this);
    addAndMakeVisible(delayFeedback);

    delayWet.setRange(0.0f, 100.0f);
    delayWet.setValue(1.0f);
    delayWet.addListener(this);
    addAndMakeVisible(delayWet);
    //EQ


    hiEqFreqKnob.setRange(3000.0f, 5000.0f, 10.0f);
    hiEqFreqKnob.setValue(4500.0f);
    hiEqFreqKnob.addListener(this);
    addAndMakeVisible(hiEqFreqKnob);
    
    hiEqQKnob.setRange(0.01f, 1.5f, 0.01f);
    hiEqQKnob.setValue(0.1f);
    hiEqQKnob.addListener(this);
    addAndMakeVisible(hiEqQKnob);
    
    hiEqGainKnob.setRange(-12.0f, 12.0f, 1.0f);
    hiEqGainKnob.setValue(1.0f);
    hiEqGainKnob.addListener(this);
    addAndMakeVisible(hiEqGainKnob);

    midEqFreqKnob.setRange(500.0f, 3000.0, 10.0f);
    midEqFreqKnob.setValue(600.0f);
    midEqFreqKnob.addListener(this);
    addAndMakeVisible(midEqFreqKnob);

    midEqQKnob.setRange(0.01f, 1.5f, 0.01f);
    midEqQKnob.setValue(0.1f);
    midEqQKnob.addListener(this);
    addAndMakeVisible(midEqQKnob);

    midEqGainKnob.setRange(-12.0f, 12.0f, 0.5f);
    midEqGainKnob.setValue(1.0f);
    midEqGainKnob.addListener(this);
    addAndMakeVisible(midEqGainKnob);

    //BYPASSING
    audioProcessor.bypassReverb();
    audioProcessor.bypassCab();
    audioProcessor.bypassReverb();
    audioProcessor.bypassDist();
    audioProcessor.bypassDelay();
    audioProcessor.bypassTube();
    audioProcessor.bypassNgPre();
    audioProcessor.bypassNgPost();

    //OTHER BTNS
    bypassCabSim.setButtonText("CAB");
    bypassCabSim.addListener(this);
    addAndMakeVisible(bypassCabSim);
    bypassCabSim.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::mediumvioletred);

    addAndMakeVisible(bypassVerbBtn);
    bypassVerbBtn.setButtonText("VERB");
    bypassVerbBtn.addListener(this);
    bypassVerbBtn.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::mediumvioletred);


    addAndMakeVisible(bypassDistBtn);
    bypassDistBtn.setButtonText("DIST");
    bypassDistBtn.addListener(this);
    bypassDistBtn.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::mediumvioletred);


    addAndMakeVisible(bypassNgPre);
    bypassNgPre.setButtonText("NOISE GATE PRE DIST");
    bypassNgPre.addListener(this);
    bypassNgPre.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::mediumvioletred);


    addAndMakeVisible(bypassNgPost);
    bypassNgPost.setButtonText("NOISE GATE POST DIST");
    bypassNgPost.addListener(this);
    bypassNgPost.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::mediumvioletred);


    addAndMakeVisible(bypassTube);
    bypassTube.setButtonText("TUBE");
    bypassTube.addListener(this);
    bypassTube.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::mediumvioletred);


    addAndMakeVisible(loadIrBtn);
    loadIrBtn.setButtonText("LOAD IR");
    loadIrBtn.addListener(this);


    tunerBtn.setButtonText("TUNER");
    tunerBtn.addListener(this);
    addAndMakeVisible(tunerBtn);


    addAndMakeVisible(bypassDelay);
    bypassDelay.setButtonText("DELAY");
    bypassDelay.addListener(this);
    bypassDelay.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::mediumvioletred);

    //lbl

    lblNgPreThreshold.setText("Thresh pre", juce::dontSendNotification);
    lblNgPreRatio.setText("Ratio", juce::dontSendNotification);
    lblNgPreAtk.setText("Attack", juce::dontSendNotification);
    lblNgPreRel.setText("Release", juce::dontSendNotification);
    lblNgPostThreshold.setText("Thresh post", juce::dontSendNotification);
    lblNgPostRatio.setText("Ratio", juce::dontSendNotification);
    lblNgPostAtk.setText("Attack", juce::dontSendNotification);
    lblNgPostRel.setText("Release", juce::dontSendNotification);


    lblMainGain.setText("Boost", juce::dontSendNotification);
    lblInputLp.setText("Tighten LP", juce::dontSendNotification);



    lblDistSel         .setText("Dist Type", juce::dontSendNotification);
    lblDistDrive       .setText("Distortion Level", juce::dontSendNotification);
    lblDistCeiling     .setText("Squash", juce::dontSendNotification);
    lblDistMix         .setText("Distortion Mix", juce::dontSendNotification);
    lblDistThresh      .setText("Slam", juce::dontSendNotification);

    lblRoomSize        .setText("Room Size", juce::dontSendNotification);
    lblDampening       .setText("Dampening", juce::dontSendNotification);
    lblRvbDry       .setText("Reverb Dry", juce::dontSendNotification);
    lblRvbWet       .setText("Reverb Wet", juce::dontSendNotification);
    lblRvbWidth       .setText("Reverb Width", juce::dontSendNotification);

    lbltubeMix         .setText("Tube Mix",juce::dontSendNotification);
    lbltubeIG          .setText("Tube Input Gain",juce::dontSendNotification);
    lbltubeOG          .setText("Tube Output Gain",juce::dontSendNotification);
    lbltubeBias        .setText("Tube Bias",juce::dontSendNotification);
    lbltubeDrive       .setText("Tube Drive",juce::dontSendNotification);
    lbldelayTime       .setText("Delay Time",juce::dontSendNotification);
    lbldelayFeedback   .setText("Delay Feedback",juce::dontSendNotification);
    lbldelayWet        .setText("Delay Mix",juce::dontSendNotification);

    
    juce::Font parameterLabel("Arial", 12.0f, juce::Font::bold);

    lblMainGain.setFont(parameterLabel);
    lblInputLp.setFont(parameterLabel);


    lblNgPreThreshold  .setFont(parameterLabel);
    lblNgPostThreshold  .setFont(parameterLabel);

    lblNgPreRatio.setFont(parameterLabel);
    lblNgPostRatio.setFont(parameterLabel);

    lblNgPreAtk.setFont(parameterLabel);
    lblNgPostAtk.setFont(parameterLabel);
    lblNgPreRel.setFont(parameterLabel);
    lblNgPostRel.setFont(parameterLabel);

    lblDistSel         .setFont(parameterLabel);
    lblDistDrive       .setFont(parameterLabel);
    lblDistCeiling     .setFont(parameterLabel);
    lblDistMix         .setFont(parameterLabel);
    lblDistThresh      .setFont(parameterLabel);
    lblRoomSize        .setFont(parameterLabel);
    lblDampening       .setFont(parameterLabel);
    lbltubeMix         .setFont(parameterLabel);
    lbltubeIG          .setFont(parameterLabel);
    lbltubeOG          .setFont(parameterLabel);
    lbltubeBias        .setFont(parameterLabel);
    lbltubeDrive       .setFont(parameterLabel);
    lbldelayTime       .setFont(parameterLabel);
    lbldelayFeedback   .setFont(parameterLabel);
    lbldelayWet        .setFont(parameterLabel);

    //tuner

    lblMainGain.setColour(juce::Label::textColourId, juce::Colours::white);
    lblInputLp.setColour(juce::Label::textColourId, juce::Colours::white);

    lblNgPreThreshold .setColour(juce::Label::textColourId, juce::Colours::white);
    lblNgPostThreshold.setColour(juce::Label::textColourId, juce::Colours::white);
    lblNgPreRatio.setColour(juce::Label::textColourId, juce::Colours::white);
    lblNgPostRatio.setColour(juce::Label::textColourId, juce::Colours::white);
    lblNgPreAtk.setColour(juce::Label::textColourId, juce::Colours::white);
    lblNgPostAtk.setColour(juce::Label::textColourId, juce::Colours::white);
    lblNgPreRel.setColour(juce::Label::textColourId, juce::Colours::white);
    lblNgPostRel.setColour(juce::Label::textColourId, juce::Colours::white);


    lblDistSel        .setColour(juce::Label::textColourId, juce::Colours::white);
    lblDistDrive      .setColour(juce::Label::textColourId, juce::Colours::white);
    lblDistCeiling    .setColour(juce::Label::textColourId, juce::Colours::white);
    lblDistMix        .setColour(juce::Label::textColourId, juce::Colours::white);
    lblDistThresh     .setColour(juce::Label::textColourId, juce::Colours::white);
    lblRoomSize       .setColour(juce::Label::textColourId, juce::Colours::white);
    lblDampening      .setColour(juce::Label::textColourId, juce::Colours::white);
    lbltubeMix        .setColour(juce::Label::textColourId, juce::Colours::white);
    lbltubeIG         .setColour(juce::Label::textColourId, juce::Colours::white);
    lbltubeOG         .setColour(juce::Label::textColourId, juce::Colours::white);
    lbltubeBias       .setColour(juce::Label::textColourId, juce::Colours::white);
    lbltubeDrive      .setColour(juce::Label::textColourId, juce::Colours::white);
    lbldelayTime      .setColour(juce::Label::textColourId, juce::Colours::white);
    lbldelayFeedback  .setColour(juce::Label::textColourId, juce::Colours::white);
    lbldelayWet       .setColour(juce::Label::textColourId, juce::Colours::white);


    addAndMakeVisible(lblTunerNote);
    addAndMakeVisible(lblTunerOffsetCents);

    addAndMakeVisible(lblNgPreThreshold);
    addAndMakeVisible(lblNgPostThreshold);

    addAndMakeVisible(lblNgPreRatio);
    addAndMakeVisible(lblNgPostRatio);

    addAndMakeVisible(lblNgPreRel);
    addAndMakeVisible(lblNgPostRel);

    addAndMakeVisible(lblNgPreAtk);
    addAndMakeVisible(lblNgPostAtk);

    addAndMakeVisible(lblDistSel);
    addAndMakeVisible(lblDistDrive);
    addAndMakeVisible(lblDistCeiling);
    addAndMakeVisible(lblDistMix);
    addAndMakeVisible(lblDistThresh);
    addAndMakeVisible(lblRoomSize);
    addAndMakeVisible(lblDampening);
    addAndMakeVisible(lblRvbDry);
    addAndMakeVisible(lblRvbWet);
    addAndMakeVisible(lblRvbWidth);

    addAndMakeVisible(lbltubeMix);
    addAndMakeVisible(lbltubeIG);
    addAndMakeVisible(lbltubeOG);
    addAndMakeVisible(lbltubeBias);
    addAndMakeVisible(lbltubeDrive);
    addAndMakeVisible(lbldelayTime);
    addAndMakeVisible(lbldelayFeedback);
    addAndMakeVisible(lbldelayWet);


    addAndMakeVisible(lblMainGain);
    addAndMakeVisible(lblInputLp);

}

DistAdvAudioProcessorEditor::~DistAdvAudioProcessorEditor()
{
    ngPreThreshSlider       .removeListener(this);
    ngPreRatioSlider        .removeListener(this);
    ngPreAtkSlider          .removeListener(this);
    ngPreRelSlider          .removeListener(this);
    ngPostThreshSlider      .removeListener(this);
    ngPostRatioSlider       .removeListener(this);
    ngPostAtkSlider         .removeListener(this);
    ngPostRelSlider         .removeListener(this);
    reverbDampingSlider     .removeListener(this);
    bypassDistBtn           .removeListener(this);
    bypassVerbBtn           .removeListener(this);
    bypassCabSim            .removeListener(this);
    loadIrBtn               .removeListener(this);
    reverbRoomSizeSlider    .removeListener(this);
    threshSlider            .removeListener(this);
    distSelect              .removeListener(this);
}


//==============================================================================
void DistAdvAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(20.0f));


    //tuner
    if (audioProcessor.tunerOn) {
        float note = round(log(audioProcessor.tunerfrequency / 440.0) / log(2) * 12 + 69);
        noteName = juce::MidiMessage::getMidiNoteName(note, true, true, 4);
        auto currentAbs = juce::MidiMessage::getMidiNoteInHertz(note);
        float offset = 1200 * log(audioProcessor.tunerfrequency / currentAbs) / log(2);
        offsetTune = juce::String(offset).formatted("%.2f", offset);

        juce::Font Tuner("Arial", 25.0f, juce::Font::bold);
        lblTunerNote.setVisible(true);
        lblTunerNote.setText(noteName, juce::dontSendNotification);
        lblTunerNote.setFont(Tuner);
        lblTunerOffsetCents.setVisible(true);
        lblTunerOffsetCents.setText(offsetTune, juce::dontSendNotification);
        lblTunerOffsetCents.setFont(Tuner);


        if (offset < 10.0f && offset >= -10.0f) {
            lblTunerNote.setColour(juce::Label::textColourId, juce::Colours::green);
        }

        lblTunerNote.setColour(juce::Label::textColourId, juce::Colours::orange);
        lblTunerOffsetCents.setColour(juce::Label::textColourId, juce::Colours::orange);
    }
    else {
        lblTunerNote.setVisible(false);
        lblTunerOffsetCents.setVisible(false);

    }

}

void DistAdvAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();

    distSelect.setBounds(20, 600, 100, 30);
    gainKnob.setBounds(240, 600, 80, 80);
    lowpassInSlider.setBounds(320, 600, 80, 80);

    scopeComponent.setBounds(0, 0, area.getWidth(), 100);

    driveSlider.setBounds(20,               120, 300, 20);                                     
    threshSlider.setBounds(20,              140, 300,   20);
    ceilingSlider.setBounds(20,             160, 300,  20);
    mixSlider.setBounds(20,                 180, 300,      20);                                       
    tubeMix.setBounds(20,                   200, 300,   20);
    tubeIG.setBounds(20,                 220, 300, 20);
    tubeOG.setBounds(20,                  240, 300,  20);
    tubeBias.setBounds(20,                    260, 300,    20);
    tubeDrive.setBounds(20,                    280, 300,    20);
    delayTime.setBounds(20,                 300, 300,     20);
    delayFeedback.setBounds(20,             320, 300, 20);
    delayWet.setBounds(20,                  340, 300,      20);
    reverbRoomSizeSlider.setBounds(20,      360, 300, 20);
    reverbDampingSlider.setBounds(20,       380, 300, 20);
    reverbWidthSlider.setBounds(20,         400, 300, 20);
    reverbWetLevel.setBounds(20,            420, 300, 20);
    reverbDryLevel.setBounds(20,            440, 300, 20);

    midEqFreqKnob.setBounds(20, 460, 300, 20);
    midEqGainKnob.setBounds(20, 480, 300, 20);
    midEqQKnob.setBounds(20, 500, 300, 20);
    hiEqFreqKnob.setBounds(20, 520, 300, 20);
    hiEqGainKnob.setBounds(20, 540, 300, 20);
    hiEqQKnob.setBounds(20, 560, 300, 20);
    //gates
    ngPreThreshSlider  .setBounds(500, 140, 80, 80);
    ngPreRatioSlider   .setBounds(580, 140, 80, 80);
    ngPreAtkSlider     .setBounds(500, 220, 80, 80);
    ngPreRelSlider     .setBounds(580, 220, 80, 80);
    ngPostThreshSlider .setBounds(500, 300, 80, 80);
    ngPostRatioSlider  .setBounds(580, 300, 80, 80);
    ngPostAtkSlider    .setBounds(500, 380, 80, 80);
    ngPostRelSlider    .setBounds(580, 380, 80, 80);

    lblNgPreThreshold.setBounds(500,  130, 100, 20);
    lblNgPreRatio.setBounds(580,      130, 100, 20);
    lblNgPreAtk.setBounds(500,        210, 100, 20);
    lblNgPreRel.setBounds(580,        210, 100, 20);


    lblNgPostThreshold.setBounds(500, 290, 100, 20);
    lblNgPostRatio.setBounds(580,     290, 100, 20);
    lblNgPostAtk.setBounds(500,       370, 100, 20);
    lblNgPostRel.setBounds(580,       370, 100, 20);



    //lblNgPreRatio.setBounds(580, 130, 100, 20);
    //lblNgPostRatio.setBounds(580, 290, 100, 20);


    //buttons (mostly bypasses) - in order left to right
    bypassCabSim.setBounds(20, 70, 80, 50);
    bypassVerbBtn.setBounds(100, 70, 80, 50);
    bypassDistBtn.setBounds(180, 70, 80, 50);
    loadIrBtn.setBounds(260, 70, 70, 50);
    bypassTube.setBounds(340, 70, 80, 50);
    bypassDelay.setBounds(420, 70, 80, 50);
    bypassNgPre.setBounds(500, 70, 80, 50);
    bypassNgPost.setBounds(580, 70, 80, 50);
    tunerBtn.setBounds(580, 460, 80, 50);





    //labels etc
    lblDistSel        .setBounds(150, 590, 50, 30);
    lblMainGain        .setBounds(260, 590, 100, 30);
    lblInputLp        .setBounds(320, 590, 100, 30);

                                        
    lblDistDrive      .setBounds(350, 120, 90, 30);
    lblDistCeiling    .setBounds(350, 140, 90, 30);
    lblDistMix        .setBounds(350, 160, 90, 30);
    lblDistThresh     .setBounds(350, 180, 90, 30);     
    lbltubeMix        .setBounds(350, 200, 90, 30);
    lbltubeIG         .setBounds(350, 220, 90, 30);
    lbltubeOG         .setBounds(350, 240, 90, 30);
    lbltubeBias       .setBounds(350, 260, 90, 30);
    lbltubeDrive      .setBounds(350, 280, 90, 30);                 
    lbldelayTime      .setBounds(350, 300, 90, 30);
    lbldelayFeedback  .setBounds(350, 320, 90, 30);
    lbldelayWet       .setBounds(350, 340, 90, 30);
    lblRoomSize       .setBounds(350, 360, 90, 30);
    lblDampening      .setBounds(350, 380, 90, 30);
    lblRvbWidth       .setBounds(350, 400, 90, 30);
    lblRvbWet         .setBounds(350, 420, 90, 30);
    lblRvbDry         .setBounds(350, 440, 90, 30);



    lblTunerNote.setBounds(600, 500, 50, 50);
    lblTunerOffsetCents.setBounds(600, 525, 100, 50);

}
void DistAdvAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &reverbRoomSizeSlider 
        || slider == &reverbDampingSlider 
        || slider == &reverbWetLevel 
        || slider == &reverbWidthSlider
        || slider == &reverbDryLevel)
    {
        juce::dsp::Reverb::Parameters params;
        params.roomSize = reverbRoomSizeSlider.getValue();
        params.damping = reverbDampingSlider.getValue();
        params.width = reverbWidthSlider.getValue();
        params.wetLevel = reverbWetLevel.getValue();
        params.dryLevel = reverbDryLevel.getValue();
        audioProcessor.setReverbParameters(params);
    }
    if (slider == &gainKnob) {
        audioProcessor.setGainKnob(gainKnob.getValue());
    }
    if (slider == &driveSlider) {
        audioProcessor.setDist(driveSlider.getValue());
    }
    if (slider == &lowpassInSlider) {
        audioProcessor.setFilterInFreq(lowpassInSlider.getValue());
    }
    if (slider == &tubeDrive) {
        audioProcessor.setTubeDrive(tubeDrive.getValue());
    }
    if (slider == &tubeIG) {
        audioProcessor.setTubeInputGain(tubeIG.getValue());
    }
    if (slider == &tubeOG) {
        audioProcessor.setTubeOutputGain(tubeOG.getValue());
    }
    if (slider == &tubeBias) {
        audioProcessor.setTubeBias(tubeBias.getValue());
    }
    if (slider == &tubeMix) {
        audioProcessor.setTubeMix(tubeMix.getValue());
    }
    if (slider == &ceilingSlider) {
        audioProcessor.setCeiling(ceilingSlider.getValue());
    }
    if (slider == &threshSlider) {
        audioProcessor.setThresh(threshSlider.getValue());
    }
    if (slider == &delayTime) {
        audioProcessor.setDelay(delayTime.getValue());
    }
    if (slider == &delayFeedback) {
        audioProcessor.setDelayFb(delayFeedback.getValue());
    }
    if (slider == &delayWet) {
        audioProcessor.setDelayWet(delayWet.getValue());
    }
    if (slider == &ngPreThreshSlider) {
        audioProcessor.setNgPreThresh(ngPostThreshSlider.getValue());
    }

    if (slider == &ngPreRatioSlider) {
        audioProcessor.setNgPreRatio(ngPreRatioSlider.getValue());
    }

    if (slider == &ngPreAtkSlider) {
        audioProcessor.setNgPreAtk(ngPreAtkSlider.getValue());
    }
    if (slider == &ngPreRelSlider) {
        audioProcessor.setNgPreRel(ngPreRelSlider.getValue());
    }
    // post
    if (slider == &ngPostThreshSlider) {
        audioProcessor.setNgPostThresh(ngPostThreshSlider.getValue());
    }

    if (slider == &ngPostRatioSlider) {
        audioProcessor.setNgPostRatio(ngPostRatioSlider.getValue());
    }

    if (slider == &ngPostAtkSlider) {
        audioProcessor.setNgPreAtk(ngPostAtkSlider.getValue());
    }
    if (slider == &ngPostRelSlider) {
        audioProcessor.setNgPostRel(ngPostRelSlider.getValue());
    }
    //eq
    //     
    if (slider == &hiEqFreqKnob) {
        audioProcessor.setHiFreq(hiEqFreqKnob.getValue());
    }
    if (slider == &hiEqQKnob) {
        audioProcessor.setHiQ(hiEqQKnob.getValue());
    }
    if (slider == &hiEqGainKnob) {
        audioProcessor.setHiGain(hiEqGainKnob.getValue());
    }
    //setMidFreq
    if (slider == &midEqFreqKnob) {
        audioProcessor.setMidFreq(midEqFreqKnob.getValue());
    }
    if (slider == &midEqQKnob) {
        audioProcessor.setMidQ(midEqQKnob.getValue());
    }
    if (slider == &midEqGainKnob) {
        audioProcessor.setMidGain(midEqGainKnob.getValue());
    }

}

void DistAdvAudioProcessorEditor::buttonClicked(juce::Button* btn) {
    juce::Button& currBtnRef = *btn;
    if (btn == &bypassVerbBtn)
    {
        bool x = audioProcessor.bypassReverb();
        if (x) {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palevioletred);
        }
        else {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palegreen);

        }
    }
    
    if (btn == &tunerBtn)
    {
        audioProcessor.bypassTuner();
    }

    if (btn == &bypassCabSim)
    {
        bool x = audioProcessor.bypassCab();
        if (x) {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palevioletred);
        }
        else {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palegreen);

        }
    }
    if (btn == &bypassDistBtn)
    {
        bool x = audioProcessor.bypassDist();
        if (x) {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palevioletred);
        }
        else {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palegreen);

        }
    }
    if (btn == &bypassTube) {
        bool x = audioProcessor.bypassTube();
        if (x) {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palevioletred);
        }
        else {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palegreen);

        }
    }
    if (btn == &bypassDelay) {
        bool x = audioProcessor.bypassDelay();
        if (x) {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palevioletred);
        }
        else {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palegreen);
        }
    }
    if (btn == &bypassNgPre) {
        bool x = audioProcessor.bypassNgPre();
        if (x) {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palevioletred);
        }
        else {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palegreen);

        }
    }
    if (btn == &bypassNgPost) {
        bool x = audioProcessor.bypassNgPost();
        if (x) {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palevioletred);
        }
        else {
            currBtnRef.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::palegreen);

        }
    }
    if (btn == &loadIrBtn) {
        filechooser = std::make_unique<juce::FileChooser>("Choose File", audioProcessor.root, "*");

        const auto fileChooserFlags = juce::FileBrowserComponent::openMode |
            juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::canSelectDirectories;

        filechooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
            {
                juce::File result(chooser.getResult());
                if (result.getFileExtension() == ".wav") {
                    audioProcessor.saveFile = result;
                    audioProcessor.root = result.getParentDirectory().getFullPathName();
                    audioProcessor.setCab(audioProcessor.saveFile);

                }
            });
    }


}
void DistAdvAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &distSelect)
    {
        int selectedId = distSelect.getSelectedId();
        // Handle the selection change here
        audioProcessor.updateParameters(selectedId);

        juce::Logger::writeToLog("Selected ID: " + juce::String(selectedId));
    }
}