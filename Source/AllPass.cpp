/*
  ==============================================================================

    AllPassFilter.cpp
    Created: 30 Oct 2017 2:26:37pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "AllPass.h"
#include <math.h>
#include "Inlet.h"
#include "Outlet.h"
#include "Delay.h"
#include "Gain.h"
#include "Sum.h"
#include "math.h"

Allpass::Allpass(float delayTime, float gain) :
    delay(delayTime),
    directGain(gain),
    feedbackGain(-gain),
    outGain(1.0 - gain * gain)
{
    // inlet >> inSum >> delay >> outGain >> outSum >> outlet;
    // delay >> feedbackGain >> inSum;
    // inlet >> directGain >> outSum;
    
    inlet >> inSum >> delay >> outSum >> outlet;
    inlet >> directGain >> outSum;
    outlet >> feedbackGain >> inSum;
}

float Allpass::process(float t, float x)
{
    begin();
    float in = first(t, x);
    float out = outlet.run(t, in);
    return finish(out);
}