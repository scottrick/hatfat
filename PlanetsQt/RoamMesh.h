#ifndef ROAMMESH_H
#define ROAMMESH_H

#include "hatfat/glee/GLee.h"

#include <list>
using namespace std;

class ZDiamond;
class ZTriangle;
class ZVertexArray;

class RoamMesh
{
public:
    RoamMesh();
    ~RoamMesh();

    void                render();
    void                toggleWireframe();

protected:
    ZVertexArray        *m_pVertexArray;

    list<ZTriangle *>   m_Triangles;
    list<ZDiamond *>    m_Diamonds;

    GLuint              indexBuffer;
    unsigned short      *m_pIndices; //index buffer

    void                setVertexArray(ZVertexArray *newArray);
    void                update();

private:
    void                initGL();

    void                setupBaseTriangles();

    bool                bGLReady;
    bool                bWireframe;
};

#endif // ROAMMESH_H
