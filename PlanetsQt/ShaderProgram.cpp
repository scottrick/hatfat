#include "ShaderProgram.h"

#include "FragmentShader.h"
#include "Options.h"
#include "VertexShader.h"

#include <cstdio>
#include <iostream>
using namespace std;

ShaderProgram::ShaderProgram(const char *pFragmentFile, const char *pVertexFile, const char *pName)
{
    Init();

    this->m_pProgramName = pName;

    FragmentShader *pFragmentShader = new FragmentShader(pFragmentFile);
    VertexShader *pVertexShader	= new VertexShader(pVertexFile);

    SetFragmentShader(pFragmentShader);
    SetVertexShader(pVertexShader);

    pFragmentShader->Release();
    pVertexShader->Release();

    CreateProgram();
}

ShaderProgram::ShaderProgram(FragmentShader *pFragmentShader, VertexShader *pVertexShader, const char *pName)
{
    Init();

    this->m_pProgramName = pName;

    SetFragmentShader(pFragmentShader);
    SetVertexShader(pVertexShader);

    CreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    DeleteProgram();
    SetFragmentShader(0);
    SetVertexShader(0);
    SetOptions(0);
}	

void ShaderProgram::Activate()
{
    glUseProgram(GetProgram());
    SetupProgram();
}

void ShaderProgram::CreateProgram()
{
    //delete current program, if any
    DeleteProgram();

    if (m_pFragmentShader && m_pVertexShader)
    {
        m_dwProgram = glCreateProgram();
        glAttachShader(m_dwProgram, m_pFragmentShader->GetShader());
        glAttachShader(m_dwProgram, m_pVertexShader->GetShader());
        glLinkProgram(m_dwProgram);
    }
}

void ShaderProgram::DeleteProgram()
{
    if (m_dwProgram >= 0)
    {
        glDeleteProgram(m_dwProgram);
    }
}

GLint ShaderProgram::GetUniformLoc(GLuint program, const GLchar *name)
{
    GLint loc;

    loc = glGetUniformLocation(program, name);

    if (loc == -1)
    {
        cout << "No uniform variable named " << name << " found!" << endl;
    }

    return loc;
}

void ShaderProgram::HideOptions() const
{
    if (m_pOptions)
    {
        m_pOptions->Hide();
    }
}

void ShaderProgram::Init()
{
    m_dwProgram			= -1;
    m_pFragmentShader	= 0;
    m_pVertexShader		= 0;
    m_pOptions			= 0;
}	

void ShaderProgram::Print(int indent) const
{
    printf("%*sShaderProgram 0x%p\n", indent, " ", this);

    if (m_pFragmentShader)
    {
        m_pFragmentShader->Print(indent + 1);
    }

    if (m_pVertexShader)
    {
        m_pVertexShader->Print(indent + 1);
    }
}

void ShaderProgram::SetFragmentShader(FragmentShader *pShader)
{
    if (m_pFragmentShader != pShader)
    {
        if (m_pFragmentShader)
        {
            m_pFragmentShader->Release();
            m_pFragmentShader = 0;
        }

        if (pShader)
        {
            m_pFragmentShader = pShader;
            m_pFragmentShader->AddRef();
        }
    }
}

void ShaderProgram::SetVertexShader(VertexShader *pShader)
{
    if (m_pVertexShader != pShader)
    {
        if (m_pVertexShader)
        {
            m_pVertexShader->Release();
            m_pVertexShader = 0;
        }

        if (pShader)
        {
            m_pVertexShader = pShader;
            m_pVertexShader->AddRef();
        }
    }
}

void ShaderProgram::SetOptions(Options *pOptions)
{
    if (m_pOptions != pOptions)
    {
        if (m_pOptions)
        {
            m_pOptions->Release();
            m_pOptions = 0;
        }

        if (pOptions)
        {
            m_pOptions = pOptions;
            m_pOptions->AddRef();
        }
    }
}

void ShaderProgram::ShowOptions() const
{
    if (m_pOptions)
    {
        m_pOptions->Show();
    }
}
