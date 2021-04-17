/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SimpleMeter.h"



//==============================================================================
FasterMasterv1AudioProcessorEditor::FasterMasterv1AudioProcessorEditor (FasterMasterv1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    mixSlider.addListener(this); // listen to user interaction with this GUI window
    mixSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); // Circular knob
    mixSlider.setBounds(100,90,200,200); // position on GUI
    mixSlider.setRange(0.f,1.f,.01f);
    //mixSlider.setSkewFactorFromMidPoint(1.f);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 30);
    mixSlider.setValue(audioProcessor.mix);
    addAndMakeVisible(mixSlider);
    
    muteButton.addListener(this);
    muteButton.setBounds(300,20,120,20);
    muteButton.setButtonText("Bypass");
    muteButton.setToggleState(audioProcessor.muteOn, juce::dontSendNotification);
    addAndMakeVisible(muteButton);
    
    meterIn.setBounds(68, 120, 15, 100);
    meterIn.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(meterIn);
    
    meterOut.setBounds(318, 120, 15, 100);
    meterOut.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(meterOut);
    
    startTimerHz(20);

}

FasterMasterv1AudioProcessorEditor::~FasterMasterv1AudioProcessorEditor()
{
}

//==============================================================================
void FasterMasterv1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll (juce::Colour(juce::Colours::lightgrey));

    g.setColour (juce::Colours::red);
    g.setFont (20.0f);
    //g.drawFittedText ("My Distortion Plug-in", getLocalBounds(), juce::Justification::centred, 1);
    g.drawFittedText ("FASTER MASTER by DFITZ",125,30, 150,65,juce::Justification::centred,1 );
    
    g.setColour (juce::Colours::black);
    g.setFont (10.0f);
    //g.drawFittedText ("My Distortion Plug-in", getLocalBounds(), juce::Justification::centred, 1);
    g.drawFittedText ("INPUT",0,200, 150,65,juce::Justification::centred,1 );
    g.drawFittedText ("OUTPUT",251,200, 150,65,juce::Justification::centred,1 );
  
    sliderAttachments.emplace_back(new AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,"mix",mixSlider));
}

void FasterMasterv1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


void FasterMasterv1AudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
    
    if (slider == &mixSlider){
        audioProcessor.mix = mixSlider.getValue();
    }
}

void FasterMasterv1AudioProcessorEditor::buttonClicked(juce::Button * button){
    
    if (button == &muteButton){
        audioProcessor.muteOn = !audioProcessor.muteOn;
    }
}

void FasterMasterv1AudioProcessorEditor::timerCallback(){
    meterIn.update(audioProcessor.meterValIn);
    meterOut.update(audioProcessor.meterValOut);
}

