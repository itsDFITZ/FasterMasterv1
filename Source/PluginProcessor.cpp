/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/


#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "RMSComp.h"
#include "SoftClip.h"
#include "VUAnalysis.h"


//==============================================================================
FasterMasterv1AudioProcessor::FasterMasterv1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

FasterMasterv1AudioProcessor::~FasterMasterv1AudioProcessor()
{
}

//==============================================================================
const juce::String FasterMasterv1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FasterMasterv1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FasterMasterv1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FasterMasterv1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FasterMasterv1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FasterMasterv1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FasterMasterv1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void FasterMasterv1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FasterMasterv1AudioProcessor::getProgramName (int index)
{
    return {};
}

void FasterMasterv1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FasterMasterv1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    rmsComp.comp.prepare(spec);
    rmsComp.comp.setRatio(20.f);
    rmsComp.comp.setAttack(3.f);
    rmsComp.comp.setRelease(.03f);
    rmsComp.comp.setThreshold(-12.f);
}

void FasterMasterv1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FasterMasterv1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FasterMasterv1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
   auto totalNumOutputChannels = getTotalNumOutputChannels();
    

   for (auto channel = totalNumInputChannels; channel < totalNumOutputChannels; ++channel)
        buffer.clear (channel, 0, buffer.getNumSamples());

       
//  Loop to go through each sample in each buffer in each channel
       for (int channel = 0; channel < totalNumOutputChannels; ++channel){
       for (int n = 0; n < buffer.getNumSamples() ; ++n){
            float x = buffer.getReadPointer(channel)[n];
            dry = x;
           
//  Write values to meter for input, if bypassed, output vals are the same
            meterValIn = VUAnalysis.processSample(x,channel);
        if (muteOn){
            meterValOut =VUAnalysis.processSample(x, channel);
            buffer.getWritePointer(channel)[n] = x;
        }else{
            
//   If not bypassed..
//   Compress
          x = rmsComp.processSample(channel,x);
//   Clip
          x = softClip.processSample(x,channel);
//   Mix
          x = mix * x + (1.f - mix) * dry;
          meterValOut = VUAnalysis.processSample(x, channel);
          buffer.getWritePointer(channel)[n] = x;
        }}
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//
//        // ..do something to the data...
//    }
       }}

//==============================================================================
bool FasterMasterv1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FasterMasterv1AudioProcessor::createEditor()
{
    return new FasterMasterv1AudioProcessorEditor (*this);
}

//==============================================================================
void FasterMasterv1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FasterMasterv1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FasterMasterv1AudioProcessor();
}
