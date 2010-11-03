#ifndef _TOON_PROGRAM_
#define _TOON_PROGRAM_

#include "ShaderProgram.h"

class ToonProgram : public ShaderProgram
{
public:
    ToonProgram(const char *pFragmentFile, const char *pVertexFile, const char *pName);


protected:
    virtual void SetupProgram();

private:


};

#endif
