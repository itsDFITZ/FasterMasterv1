//
//  Header.h
//  ExampleProject - VST3
//
//  Created by Dylan Page on 3/23/21.
//  Copyright © 2021 DFITZ SP. All rights reserved.
//

#ifndef SoftClip_h
#define SoftClip_h
//#include "PluginProcessor.h"

class SoftClip{
public:
    SoftClip(){};
   
    void softClip(float * signal, const int numSamples, const int c);
   
    float processSample(float x, int channel);
    
//    void prepare(float newFs);
private:
 
    float x;
    int thresh;
   
};


#endif /* SoftClip_h */
