#include "PlanetOptions.h"

#include "Planet.h"

#include <iostream>
using namespace std;

#define LABEL_ID							1
#define ARPEGGIATION_SCROLL_ID				5

PlanetOptions::PlanetOptions(Planet *pPlanet)
{
    Init();

    m_pPlanet = pPlanet;
}

PlanetOptions::~PlanetOptions()
{
    SetPlanet(0);
}

void PlanetOptions::Hide()
{

}

void PlanetOptions::Init()
{
    m_pPlanet	= 0;
}

void PlanetOptions::SetPlanet(Planet *pPlanet)
{
    if (m_pPlanet != pPlanet)
    {
        if (m_pPlanet)
        {
            m_pPlanet->Release();
            m_pPlanet = 0;
        }

        if (pPlanet)
        {
            m_pPlanet = pPlanet;
            m_pPlanet->AddRef();
        }
    }
}

void PlanetOptions::Show()
{

}
