#ifndef _SHADER_MANAGER_
#define _SHADER_MANAGER_

#include "ShaderProgram.h"

#include <vector>
using namespace std;

class PlanetProgramOne;

class ShaderManager
{
public:
    static ShaderManager &get()
    {
        static ShaderManager theManager;
        return theManager;
    }

    ShaderProgram       *GetActiveProgram();
    PlanetProgramOne    *GetPlanetProgram()             { return m_pPlanetProgram; }

    void NextProgram();
    void PrevProgram();

protected:


private:
    vector<ShaderProgram *>                             m_Programs;
    vector<ShaderProgram* >::iterator                   m_ProgramIter;

    PlanetProgramOne                                    *m_pPlanetProgram;

    ShaderManager();
    ShaderManager(const ShaderManager &manager);        //not defined on purpose
    ShaderManager & operator=(const ShaderManager &);   //not defined on purpose

    ~ShaderManager()                                    {};

    void													Init();
};

#endif
