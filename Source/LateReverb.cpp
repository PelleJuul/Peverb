/*
  ==============================================================================

    LateReverb.cpp
    Created: 8 Dec 2017 9:00:13am
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "LateReverb.h"
#include "AllpassFilter.h"
#include "../JuceLibraryCode/JuceHeader.h"

LateReverb::LateReverb(int sampleRate) :
    allpassAL(0.0083, 0.7, sampleRate),
    allpassBL(0.022, 0.5, sampleRate),
    allpassCL(0.030, 0.5, sampleRate),
    allpassDL(0.0098, 0.6, sampleRate),
    wrapAL([&] (float x) { return allpassBL.process(allpassAL.process(x)); }),
    nestedAL(0.035, 0.3, &wrapAL, sampleRate),
    nestedBL(0.039, 0.3, &allpassDL, sampleRate),
    delayAL(0.005, sampleRate),
    delayBL(0.067, sampleRate),
    delayCL(0.015, sampleRate),
    delayDL(0.108, sampleRate),

    allpassAR(0.0093, 0.7, sampleRate),
    allpassBR(0.023, 0.5, sampleRate),
    allpassCR(0.031, 0.5, sampleRate),
    allpassDR(0.0108, 0.6, sampleRate),
    wrapAR([&] (float x) { return allpassBR.process(allpassAR.process(x)); }),
    nestedAR(0.036, 0.3, &wrapAR, sampleRate),
    nestedBR(0.040, 0.3, &allpassDR, sampleRate),
    delayAR(0.006, sampleRate),
    delayBR(0.068, sampleRate),
    delayCR(0.016, sampleRate),
    delayDR(0.109, sampleRate)
{
    gain = 0.7;
    IIRCoefficients coeff = IIRCoefficients::makeLowPass(sampleRate, 2500);
    feedbackFilterL.setCoefficients(coeff);
    feedbackFilterR.setCoefficients(coeff);
}

void LateReverb::process(float l, float r)
{
    {
        float sum1 = l + gain * feedbackFilterL.processSingleSampleRaw(delayDR.read());
        float xNestedA = nestedAL.process(sum1);
        float xAllpassC = delayBL.process(allpassCL.process(delayAL.process(xNestedA)));
        float xNestedB = nestedBL.process(r + gain * delayCL.process(xAllpassC));
        delayDL.write(xNestedB);
        left = 0.5 * xNestedA + 0.5 * xAllpassC + 0.5 * xNestedB;
    }
    
    {
        float sum1 = r + gain * feedbackFilterR.processSingleSampleRaw(delayDL.read());
        float xNestedA = nestedAR.process(sum1);
        float xAllpassC = delayBR.process(allpassCR.process(delayAR.process(xNestedA)));
        float xNestedB = nestedBR.process(l + gain * delayCR.process(xAllpassC));
        delayDR.write(xNestedB);
        right = 0.5 * xNestedA + 0.5 * xAllpassC + 0.5 * xNestedB;
    }
}