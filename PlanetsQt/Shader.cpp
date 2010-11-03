#include <fstream>
#include <iostream>
using namespace std;

#include "Shader.h"

Shader::Shader() 
{
    m_dwShader = -1; //-1 means no shader created, etc yet
}

Shader::~Shader() 
{
    if (m_dwShader > 0)
    {
        glDeleteShader(m_dwShader);
        m_dwShader = -1;
    }
}

void Shader::LoadShader(const char *pFilename) 
{
    printf("Loading shader \"%s\" ...  ", pFilename);
    ifstream shaderFile(pFilename, ios::in | ios::binary | ios::ate);
    char	*pMemBlock		= 0;
    int		size			= 0;



    if (!shaderFile.is_open())
    { //abort if the file isn't open
        printf("FAILED\n");
        return;
    }

    size					= (int) shaderFile.tellg();
    pMemBlock				= new char[size];

    shaderFile.seekg(0, ios::beg);
    shaderFile.read(pMemBlock, size);
    shaderFile.close();

    const GLchar *pSource	= (GLchar *) pMemBlock;
    m_dwShader				= CreateShader();

    glShaderSource(m_dwShader, 1, &pSource, &size);
    delete pMemBlock;

    glCompileShader(m_dwShader);

    //Check to see if it compiled correctly
    GLint length = 0;
    glGetShaderiv(m_dwShader, GL_INFO_LOG_LENGTH, &length);

    if (length > 1)
    { //there was an error, so print it out...
        printf("\n --> ERROR compiling shader \"%s\"\n", pFilename);

        GLchar *pLog = new GLchar[length];
        GLsizei actualLength;

        glGetShaderInfoLog(m_dwShader, length, &actualLength, pLog);

        printf("%s --> END ERROR\n", pLog);
    }
    else
    {
        printf("OK\n");
    }
}
