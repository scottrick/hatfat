#include "CubeProgram.h"

CubeProgram::CubeProgram(const char *pFragmentFile, const char *pVertexFile, const char *pName)
    : ShaderProgram(pFragmentFile, pVertexFile, pName)
{

}

void CubeProgram::SetupProgram()
{
    glUseProgram(GetProgram());

    glUniform3f(GetUniformLoc(GetProgram(), "LightPosition"), 1.0f, 0.1f, 5.0f);
    glUniform3f(GetUniformLoc(GetProgram(), "LightColor"), 1.0f, 1.0f, 1.0f);
    glUniform3f(GetUniformLoc(GetProgram(), "EyePosition"), 1.0f, 2.7f, 1.6f);
    glUniform3f(GetUniformLoc(GetProgram(), "Specular"), 0.0f, 0.0f, 1.0f);
    glUniform3f(GetUniformLoc(GetProgram(), "Ambient"), 1.0f, 1.0f, 1.0f);
    glUniform1f(GetUniformLoc(GetProgram(), "Kd"), 0.1f);
}
