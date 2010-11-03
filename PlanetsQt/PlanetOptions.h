#ifndef _PLANET_OPTIONS_
#define _PLANET_OPTIONS_

#include "Options.h"

class Planet;
class SWindow;

class PlanetOptions : public Options
{
public:
    PlanetOptions(Planet *pPlanet);

    const char							*GetClassDebugName() const			{ return "PlanetOptions"; }
    virtual void						Hide();
    void								Print(int indent) const				{ }
    void								SetPlanet(Planet *pPlanet);
    virtual void						Show();

protected:
    ~PlanetOptions();

private:
    Planet *m_pPlanet;

    void								Init();

};

#endif
