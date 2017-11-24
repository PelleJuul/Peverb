/*
  ==============================================================================

    Inlet.cpp
    Created: 22 Nov 2017 9:29:33pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "Inlet.h"

float Inlet::process(float t, float x)
{
    begin();
    return finish(x);
}