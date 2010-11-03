#ifndef _SHADER_
#define _SHADER_

#include "Unknown.h"

#include "hatfat/glee/GLee.h"

class Shader : public Unknown {
public:
    Shader();

    GLuint				GetShader() const		{ return m_dwShader; }

protected:
    virtual ~Shader();

    virtual GLuint CreateShader() = 0;
    void LoadShader(const char *pFilename);

    GLuint	m_dwShader;

private:


};

#endif
