/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SoftClip.h"
#include "RMSComp.h"
#include "VUAnalysis.h"

using namespace dsp;

//==============================================================================
/**
*/
class FasterMasterv1AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    FasterMasterv1AudioProcessor();
    ~FasterMasterv1AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    AudioProcessorValueTreeState state;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    float mix = 0.f;
    bool  muteOn = false;
    float meterVal;
    float meterValIn;
    float meterValOut;
    ProcessSpec spec;
    
private:
    SoftClip softClip;
    RMSComp rmsComp;
//    float dry;
//    float wetOut;
//    float compOut;
//    float clipOut;
//    float x;
   
    
   
    VUAnalysis vuAnalysis;
    ;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FasterMasterv1AudioProcessor)
};
