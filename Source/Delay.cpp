/*
  ==============================================================================

    Delay.cpp
    Created: 8 Dec 2017 8:59:44am
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "Delay.h"
#include <vector>
#include <cmath>
#include <exception>

Delay::Delay(int sampleRate)
{
    this->sampleRate = sampleRate;
}

Delay::Delay(float maxDelay, int sampleRate)
{
    this->sampleRate = sampleRate;
    resize(maxDelay);
}

void Delay::resize(float maxDelay)
{
    this->maxDelay = maxDelay;
    auto lengthInSamples = std::ceil(maxDelay * sampleRate);
    delayBuffer.resize(lengthInSamples, 0);
    index = 0;
}

void Delay::write(float sample)
{
    delayBuffer[index % delayBuffer.size()] = sample;
    index = index + 1;
}

float Delay::read(float delay)
{
    int delayInSamples = std::ceil(delay * sampleRate);
    int delayIndex = (index - delayInSamples) % delayBuffer.size();
    return delayBuffer[delayIndex];
}

float Delay::read()
{
    int delayIndex = (index - delayBuffer.size()) % delayBuffer.size();
    return delayBuffer[delayIndex];
}

float Delay::process(float x)
{
    write(x);
    float result = read();
    return result;
}