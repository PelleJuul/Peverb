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

/*
Direct: 17.7
Early:
21.1l
27.4l
29.7l
31.6l
33.0l
75.6l

24.6r
30.9r
32.3r
35.4r
36.4r
40.7r
*/

void EarlyReflections::process(float l, float r)
{
    float x = sqrtf(0.5) * l + sqrt(0.5) * r;
    float sumL = 0.2  * delayL.read(0.0211)
               + 0.2  * delayL.read(0.0274)
               + 0.14 * delayL.read(0.0297)
               + 0.14 * delayL.read(0.0316)
               + 0.14 * delayL.read(0.0330)
               + 0.11 * delayL.read(0.0756);
    
    float sumR = 0.2  * delayR.read(0.0246)
               + 0.2  * delayR.read(0.0309)
               + 0.14 * delayR.read(0.0323)
               + 0.14 * delayR.read(0.0354)
               + 0.14 * delayR.read(0.0364)
               + 0.14 * delayR.read(0.0407);
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
