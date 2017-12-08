/*
  ==============================================================================

    NestedAllpass.cpp
    Created: 8 Dec 2017 9:39:16am
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "Nested.h"
#include "Processor.h"

Nested::Nested(float delayTime, float gain, Processor *innerProcess, int sampleRate) :
    delay(delayTime, sampleRate)
{
    this->gain = gain;
    this->innerProcess = innerProcess;
}

float Nested::process(float x)
{
    float sum2 = -gain * x + innerProcess->process(delay.read());
    float sum1 = gain * sum2 + x;
    delay.write(sum1);
    return sum2;
}