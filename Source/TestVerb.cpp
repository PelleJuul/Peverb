/*
  ==============================================================================

    TestVerb.cpp
    Created: 24 Nov 2017 10:31:51am
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "TestVerb.h"

TestVerb::TestVerb() : allpassA(0.131, 0.7), allpassB(0.0875, 0.7), allpassC(0.0541, 0.7)
{

}

float TestVerb::process(float x)
{
    float inSum = x + feedback * gain;
    
    float allpassed = inSum;
    allpassed = allpassA.process(allpassed);
    allpassed = allpassB.process(allpassed);
    allpassed = allpassC.process(allpassed);
    
    float outerOutSum = allpassed + x * -gain;
    feedback = outerOutSum;
    return  outerOutSum;
}