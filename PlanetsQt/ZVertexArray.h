#ifndef ZVERTEXARRAY_H
#define ZVERTEXARRAY_H

#include "ZVertex.h"

#include "hatfat/glee/GLee.h"

#define VERTEX_ARRAY_SIZE 65535

class ZVertexArray
{
public:
    ZVertexArray();
    ~ZVertexArray();

    unsigned short  m_StackPosition;
    unsigned short  *m_pStack;
    unsigned char   *m_pUpdated; //vertices to be updated

    ZVertex         *m_pBuffer; //vertices

    GLuint          vertexBuffer; //ogl vertex buffer id

    unsigned short  getVertex();
    void            releaseVertex(unsigned short index);
    void            updateVertex(unsigned short index);

//    void            enableVertexStuff();
//    void            disableVertexStuff();

    void            enableNormalArray();
    void            disableNormalArray();

    void            initRender();
    void            finishRender();

    void            initGL();

    ZVertex         *operator[](unsigned short index) { return &m_pBuffer[index]; }
};

#endif // ZVERTEXARRAY_H
