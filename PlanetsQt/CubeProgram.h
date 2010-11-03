#ifndef _CUBE_PROGRAM_
#define _CUBE_PROGRAM_

#include "ShaderProgram.h"

class CubeProgram : public ShaderProgram
{
public:
    CubeProgram(const char *pFragmentFile, const char *pVertexFile, const char *pName);

protected:
    virtual void SetupProgram();

private:


};

#endif
