#include "PlanetProgramOne.h"

#include "PlanetOptions.h"

#include <iostream>
using namespace std;

PlanetProgramOne::PlanetProgramOne(const char *pFragmentFile, const char *pVertexFile, const char *pName)
    : ShaderProgram(pFragmentFile, pVertexFile, pName)
{
    Init();
}

void PlanetProgramOne::Init()
{
    m_pPlanet = 0;

    SetOptions(new PlanetOptions(0));
}

void PlanetProgramOne::SetPlanet(Planet *pPlanet)
{
    if (pPlanet != m_pPlanet)
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

        ((PlanetOptions *)m_pOptions)->SetPlanet(m_pPlanet);
    }
}

void PlanetProgramOne::SetupProgram()
{
    if (m_pPlanet)
    {
        glUniform1i(GetUniformLoc(GetProgram(), "planetSeed"), m_pPlanet->GetPlanetSeed());
        glUniform1f(GetUniformLoc(GetProgram(), "planetRadius"), m_pPlanet->GetArchepeggiation());
    }
    else
    {
        glUniform1i(GetUniformLoc(GetProgram(), "planetSeed"), 4949);
        glUniform1f(GetUniformLoc(GetProgram(), "planetRadius"), 5.0f);
    }
}
