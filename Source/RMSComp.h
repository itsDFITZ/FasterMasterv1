//
//  RMSComp.h
//  ExampleProject - VST3
//
//  Created by Dylan Page on 3/23/21.
//  Copyright © 2021 DFITZ SP. All rights reserved.
//
#pragma once
#ifndef RMSComp_h
#define RMSComp_h
#include <JuceHeader.h>
//#include "juce_dsp.h"
//#include "juce_Compressor.h"

using namespace juce;


class RMSComp{
public:
    RMSComp(){};
    void rmsComp(float * signal, const int numSamples, const int c);
    void processSignal(float * signal, const int numSamples, const int c);
    float processSample(float x,int channel);

    dsp::Compressor<float> comp;
    AudioBuffer<float> buffer;

private:

    float x;
  

};


#endif /* RMSComp_h */
