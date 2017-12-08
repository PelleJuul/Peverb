/*
  ==============================================================================

    NestedAllpass.h
    Created: 8 Dec 2017 9:39:16am
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once
#include "Processor.h"
#include "Delay.h"

class Nested : Processor
{
public:
    Nested(float delayTime, float gain, Processor *innerProcess, int sampleRate);
    virtual float process(float x) override;
    
private:
    Delay delay;
    Processor *innerProcess;
    float lastY;
    float gain;
};