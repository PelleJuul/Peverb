/*
  ==============================================================================

    Chain.cpp
    Created: 23 Nov 2017 2:16:13pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "Chain.h"

Chain Chain::operator>(Chain &chain)
{
    *last >>= *chain.first;
    Chain newChain;
    newChain.first = first;
    newChain.last = chain.last;
    return newChain;
}

Chain Chain::operator>(Node &node)
{
    *last >>= node;
    Chain newChain;
    newChain.first = first;
    newChain.last = &node;
    return newChain;
}

Node& Chain::operator>>(Node &node)
{
    *last >>= node;
    return node;
}
