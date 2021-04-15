//
//  RMSComp.cpp
//  ExampleProject - VST3
//
//  Created by Dylan Page on 3/23/21.
//  Copyright © 2021 DFITZ SP. All rights reserved.
//

#include <stdio.h>
#include "RMSComp.h"
#include <math.h>
#include <JuceHeader.h>

using namespace std;

//RMSComp::RMSComp(){};

void RMSComp::rmsComp(float * x, const int numSamples, const int c){};

 

float RMSComp::processSample(float x, int channel){

    x = comp.processSample(channel,x);
  
    return x;
    };



        
    

