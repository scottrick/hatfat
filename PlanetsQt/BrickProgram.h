#ifndef _BRICK_PROGRAM_
#define _BRICK_PROGRAM_

#include "ShaderProgram.h"

class BrickProgram : public ShaderProgram
{
public:
    BrickProgram(const char *pFragmentFile, const char *pVertexFile, const char *pName);

protected:
    virtual void SetupProgram();

private:


};

#endif
