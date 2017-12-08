/*
  ==============================================================================

    EarlyReflections.cpp
    Created: 26 Nov 2017 5:50:14pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "EarlyReflections.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "Delay.h"
#include <vector>

EarlyReflections::EarlyReflections(int sampleRate) :
    delayL(0.1, sampleRate),
    delayR(0.1, sampleRate),
    binauralDelayLeft(0.0008, sampleRate),
    binauralDelayRight(0.0008, sampleRate)
{    
        /*
    // [13, 23, 31, 43, 59, 64, 73, 81]
    float a = 0.6;
    float d = 0.2;
    
    tabsLeft = {0.013, 0.031, 0.059, 0.073};
    coeffsLeft = {a, a*d, a*d*d, a*d*d*d};
    tabsRight = {0.023, 0.043, 0.064, 0.081};
    coeffsRight = {a, a*d, a*d*d, a*d*d*d};
     */
    
    IIRCoefficients coeff = IIRCoefficients::makeLowPass(44100, 2000);
    binauralLowPassLeft.setCoefficients(coeff);
    binauralLowPassRight.setCoefficients(coeff);
}

void EarlyReflections::process(float l, float r)
{
    float x = sqrtf(0.5) * l + sqrt(0.5) * r;
    float a = 0.7;
    float b = 0.3;
    float sumL = a*b * delayL.read(0.013)
               + a*b*b * delayL.read(0.031)
               + a*b*b*b + delayL.read(0.059)
               + a*b*b*b*b + delayL.read(0.073);
    float sumR = a*b * delayR.read(0.023)
               + a*b*b * delayR.read(0.043)
               + a*b*b*b * delayR.read(0.064)
               + a*b*b*b*b * delayR.read(0.081);
    delayL.write(x);
    delayR.write(x);
    
    float binauralR = binauralDelayRight.read();
    binauralR = binauralLowPassRight.processSingleSampleRaw(binauralR);
    binauralDelayRight.write(sumR);
    
    float binauralL = binauralDelayLeft.read();
    binauralL = binauralLowPassLeft.processSingleSampleRaw(binauralR);
    binauralDelayLeft.write(sumL);
    
    left = sumL + binauralR;
    right = sumR + binauralL;
}