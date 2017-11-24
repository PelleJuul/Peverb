/*
  ==============================================================================

    Sum.cpp
    Created: 22 Nov 2017 9:02:21pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "Sum.h"
#include "Node.h"

float Sum::process(float t, float x)
{
    begin();
    float sum = sumConnections(t, x);
    return finish(sum);
}