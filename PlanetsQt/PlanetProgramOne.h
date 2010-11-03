#ifndef _PLANET_PROGRAM_ONE_
#define _PLANET_PROGRAM_ONE_

#include "Planet.h"
#include "ShaderProgram.h"

class PlanetProgramOne : public ShaderProgram
{
public:
    PlanetProgramOne(const char *pFragmentFile, const char *pVertexFile, const char *pName);

    void SetPlanet(Planet *pPlanet);

protected:
    virtual void SetupProgram();

private:

    void				Init();

    Planet				*m_pPlanet;
};

#endif
