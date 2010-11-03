#include "StripeProgram.h"

StripeProgram::StripeProgram(const char *pFragmentFile, const char *pVertexFile, const char *pName)
    : ShaderProgram(pFragmentFile, pVertexFile, pName)
{

}

void StripeProgram::SetupProgram()
{
    glUseProgram(GetProgram());

    glUniform3f(GetUniformLoc(GetProgram(), "StripeColor"), 0.5f, 0.0f, 0.0f);
    glUniform3f(GetUniformLoc(GetProgram(), "BackColor"), 0.0f, 0.0f, 0.5f);
    glUniform1f(GetUniformLoc(GetProgram(), "Width"), 0.5f);
    glUniform1f(GetUniformLoc(GetProgram(), "Fuzz"), 0.01f);
    glUniform1f(GetUniformLoc(GetProgram(), "Scale"), 5.0f);

    glUniform3f(GetUniformLoc(GetProgram(), "LightPosition"), 1.0f, 0.1f, 5.0f);
    glUniform3f(GetUniformLoc(GetProgram(), "LightColor"), 1.0f, 1.0f, 1.0f);
    glUniform3f(GetUniformLoc(GetProgram(), "EyePosition"), 1.0f, 2.7f, 1.6f);
    glUniform3f(GetUniformLoc(GetProgram(), "Specular"), 1.0f, 1.0f, 1.0f);
    glUniform3f(GetUniformLoc(GetProgram(), "Ambient"), 1.0f, 1.0f, 1.0f);
    glUniform1f(GetUniformLoc(GetProgram(), "Kd"), 0.1f);
}
