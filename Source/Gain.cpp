/*
  ==============================================================================

    Gain.cpp
    Created: 22 Nov 2017 9:25:22pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "Gain.h"

Gain::Gain(float initGain)
{
    gain = initGain;
}

void Gain::setGain(float value)
{
    gain = value;
}

float Gain::process(float t, float x)
{
    begin();
    float in = first(t, x);
    return finish(in * gain);
}