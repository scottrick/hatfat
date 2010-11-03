#include "Planet.h"

#include <cstdlib>
#include <iostream>
using namespace std;

Planet::Planet()
{
    Randomize();
}

Planet::Planet(int newSeed, float fNewRadius, float fNewArchepeggiation)
{
    m_dwPlanetSeed = newSeed;
    m_fPlanetRadius = fNewRadius;
    m_fArchepeggiation = fNewArchepeggiation;
}

void Planet::Print(int indent) const
{
    cout << "Planet 0x" << this << endl;
}

void Planet::Randomize()
{
    m_dwPlanetSeed = rand();
    m_fPlanetRadius = (float) (500 + rand() % 1000000);
    m_fArchepeggiation = (float)rand() / (float)RAND_MAX * 10.0f;
}
