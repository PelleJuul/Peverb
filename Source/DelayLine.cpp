/*
  ==============================================================================

    DelayLine.cpp
    Created: 30 Oct 2017 2:26:22pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "DelayLine.h"
#include "math.h"

DelayLine::DelayLine() : samples()
{
    clear();
    sampleRate = 44100;
}

void DelayLine::setDelay(float newSize)
{
    samples.resize(newSize * 44100, 0);
}

void DelayLine::setDelaySeconds(float newSize)
{
    samples.resize(newSize * sampleRate, 0);
    index = 0;
}

void DelayLine::write(float sample)
{
    samples[index] = sample;
    index = (index + 1) % samples.size();
}

float DelayLine::read(float t) const
{
    int n = floor(t  * (float)sampleRate);
    int i = (index - n) % samples.size();
    return samples[i];
}

void DelayLine::clear()
{
    std::fill(samples.begin(), samples.end(), 0.0);
    index = 0;
}