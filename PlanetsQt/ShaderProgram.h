#ifndef _SHADER_PROGRAM_
#define _SHADER_PROGRAM_

#include "Unknown.h"

#include "hatfat/glee/GLee.h"

#include <iostream>
using namespace std;

class FragmentShader;
class Options;
class VertexShader;

class ShaderProgram : public Unknown
{
public:
    ShaderProgram(const char *pFragmentFile, const char *pVertexFile, const char *pName);
    ShaderProgram(FragmentShader *pFragmentShader, VertexShader *pVertexShader, const char *pName);

    void			Activate();

    const char		*GetClassDebugName() const			{ return "ShaderProgram"; }
    GLuint			GetProgram() const				{ return m_dwProgram; }
    const char		*GetProgramName() const			{ return m_pProgramName; }
    Options			*GetOptions() const				{ return m_pOptions; }
    void			Print(int indent) const;

    void			HideOptions() const;
    void			ShowOptions() const;

protected:
    virtual			~ShaderProgram();

    virtual void	SetupProgram()					{ };

    void			CreateProgram();
    void			DeleteProgram();
    GLint			GetUniformLoc(GLuint program, const GLchar *name);
    void			Init();
    void			SetFragmentShader(FragmentShader *pShader);
    void			SetVertexShader(VertexShader *pShader);
    void			SetOptions(Options *pOptions);

    GLuint			m_dwProgram;
    const char		*m_pProgramName;

    FragmentShader	*m_pFragmentShader;
    VertexShader	*m_pVertexShader;

    Options			*m_pOptions;

private:


};

#endif
