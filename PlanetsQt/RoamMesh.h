#ifndef ROAMMESH_H
#define ROAMMESH_H

#include "hatfat/glee/GLee.h"

class ZTriangle;
class ZVertexArray;

class RoamMesh
{
public:
    RoamMesh();
    ~RoamMesh();

    void Render();

protected:
    ZVertexArray        *m_pVertexArray;
    ZTriangle           *m_pTestTriangle;
    ZTriangle           *m_pTriTwo;

    GLuint              indexBuffer;
    unsigned short      *m_pIndices; //index buffer

    void                setVertexArray(ZVertexArray *newArray);

private:
    void                initGL();
    void                InitTest();

    bool                bGLReady;

};

#endif // ROAMMESH_H
