#ifndef _PLANET_
#define _PLANET_

#include "Unknown.h"

class Planet : public Unknown
{
public:
    Planet();
    Planet(int newSeed, float fNewRadius, float fNewArchepeggiation);

    float		GetArchepeggiation()				{ return m_fArchepeggiation; }
    const char *GetClassDebugName() const			{ return "Planet"; }
    float		GetPlanetRadius() const				{ return m_fPlanetRadius; }
    int			GetPlanetSeed() const				{ return m_dwPlanetSeed; }

    void		Print(int indent) const;

    void		Randomize();

protected:


private:
    int m_dwPlanetSeed;
    float m_fPlanetRadius; //in km
    float m_fArchepeggiation;

};

#endif
