#ifndef _TEST_TEXTURE_PROGRAM_
#define _TEST_TEXTURE_PROGRAM_

#include "ShaderProgram.h"

class TestTextureProgram : public ShaderProgram
{
public:
    TestTextureProgram(const char *pFragmentFile, const char *pVertexFile, const char *pName);

protected:
    virtual void SetupProgram();

private:


};

#endif
