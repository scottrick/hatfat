#include "BrickProgram.h"

BrickProgram::BrickProgram(const char *pFragmentFile, const char *pVertexFile, const char *pName)
    : ShaderProgram(pFragmentFile, pVertexFile, pName)
{

}

void BrickProgram::SetupProgram()
{
    glUseProgram(GetProgram());

    glUniform3f(GetUniformLoc(GetProgram(), "BrickColor"), 1.0f, 0.3f, 0.2f);
    glUniform3f(GetUniformLoc(GetProgram(), "MortarColor"), 0.85f, 0.86f, 0.84f);
    glUniform2f(GetUniformLoc(GetProgram(), "BrickSize"), 0.3f, 0.15f);
    glUniform2f(GetUniformLoc(GetProgram(), "BrickPercent"), 0.9f, 0.85f);
    glUniform3f(GetUniformLoc(GetProgram(), "LightPosition"), 1.0f, 0.1f, 5.0f);
}
