#ifndef ROAMMESH_H
#define ROAMMESH_H

#include "hatfat/glee/GLee.h"

#include <list>
using namespace std;

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

    list<ZTriangle *>   m_BaseTriangles;

    GLuint              indexBuffer;
    unsigned short      *m_pIndices; //index buffer

    void                setVertexArray(ZVertexArray *newArray);

private:
    void                initGL();

    void                setupBaseTriangles();

    bool                bGLReady;
};

#endif // ROAMMESH_H
