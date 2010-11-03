#ifndef _STRIPE_PROGRAM_
#define _STRIPE_PROGRAM_

#include "ShaderProgram.h"

class StripeProgram : public ShaderProgram
{
public:
    StripeProgram(const char *pFragmentFile, const char *pVertexFile, const char *pName);

protected:
    virtual void SetupProgram();

private:


};

#endif
