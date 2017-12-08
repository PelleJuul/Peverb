/*
  ==============================================================================

    Chain.cpp
    Created: 8 Dec 2017 10:10:09am
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "Wrap.h"
#include "Processor.h"
#include <functional>

Wrap::Wrap(std::function<float(float)> processFunc)
{
    this->processFunc = processFunc;
}

float Wrap::process(float x)
{
    return processFunc(x);
}