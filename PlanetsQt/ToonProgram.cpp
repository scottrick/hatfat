#include "ToonProgram.h"

ToonProgram::ToonProgram(const char *pFragmentFile, const char *pVertexFile, const char *pName)
    : ShaderProgram(pFragmentFile, pVertexFile, pName)
{

}

void ToonProgram::SetupProgram()
{
    glUseProgram(GetProgram());

    glUniform3f(GetUniformLoc(GetProgram(), "lightDir"), 1.0f, 0.1f, 2.0f);
}
