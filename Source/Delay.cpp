/*
  ==============================================================================

    DelayLine.cpp
    Created: 30 Oct 2017 2:26:22pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "Delay.h"
#include "math.h"

Delay::Delay(float seconds)
{
    setDelay(seconds);
}

void Delay::setDelay(float seconds)
{
    index = 0;
    size = floor(seconds * 44100);
    samples.resize(size, 0);
}

float Delay::process(float t, float x)
{
    begin();
    float in = first(t, x);
    float out = read();
    write(in);
    return finish(out);
}

void Delay::write(float sample)
{
    samples[index] = sample;
    index = (index + 1) % samples.size();
}

float Delay::read()
{
    int i = (index - size) % samples.size();
    return samples[i];
}