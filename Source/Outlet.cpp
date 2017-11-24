/*
  ==============================================================================

    Outlet.cpp
    Created: 22 Nov 2017 9:28:38pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "Outlet.h"
#include "math.h"

float Outlet::process(float t, float x)
{
    begin();
    float out = first(t, x);
    return finish(tanh(out));
}

float Outlet::run(float t, float x)
{
    prepare();
    return process(t, x);
}