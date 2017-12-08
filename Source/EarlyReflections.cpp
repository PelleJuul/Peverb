/*
  ==============================================================================

    EarlyReflections.cpp
    Created: 26 Nov 2017 5:50:14pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "EarlyReflections.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "DelayLine.h"
#include <vector>

EarlyReflections::EarlyReflections()
{
    directGain = 0.0;
    reflectGain = 1.0;
    
    delay.setDelaySeconds(0.1);
    // [13, 23, 31, 43, 59, 64, 73, 81]
    float a = 0.75;
    float d = 0.2;
    
    tabsLeft = {0.013, 0.031, 0.059, 0.073};
    coeffsLeft = {a, a*d, a*d*d, a*d*d*d};
    tabsRight = {0.023, 0.043, 0.064, 0.081};
    coeffsRight = {a, a*d, a*d*d, a*d*d*d};
    
    binauralDelayLeft.setDelaySeconds(0.0008);
    binauralDelayRight.setDelaySeconds(0.0008);
    
    IIRCoefficients coeff = IIRCoefficients::makeLowPass(44100, 2000);
    binauralLowPassLeft.setCoefficients(coeff);
    binauralLowPassRight.setCoefficients(coeff);
}

float EarlyReflections::process(float x)
{
    float sumL = 0;
    float sumR = 0;
    
    for (int i = 0; i < tabsLeft.size(); i++)
    {
        float t = tabsLeft[i];
        float a = coeffsLeft[i];
        sumL += delay.read(t) * a;
    }
    
    for (int i = 0; i < tabsRight.size(); i++)
    {
        float t = tabsRight[i];
        float a = coeffsRight[i];
        sumR += delay.read(t) * a;
    }
    delay.write(x * reflectGain);
    
    float binauralR = binauralDelayRight.read();
    binauralR = binauralLowPassRight.processSingleSampleRaw(binauralR);
    binauralDelayRight.write(sumR);
    
    float binauralL = binauralDelayLeft.read();
    binauralL = binauralLowPassLeft.processSingleSampleRaw(binauralR);
    binauralDelayLeft.write(sumL);
    
    left = sumL + binauralR + x * directGain;
    right = sumR + binauralL + x * directGain;
}