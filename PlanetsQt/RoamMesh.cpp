#include "RoamMesh.h"

#include "hatfat/glee/GLee.h"

#include "ZTriangle.h"
#include "ZVertexArray.h"

#include <iostream>
using namespace std;

#define NUMBER_OF_INDICES (128 * 1024 * 3)

RoamMesh::RoamMesh()
{
    bGLReady = false;
    bWireframe = false;

    m_pVertexArray = new ZVertexArray();

    m_pIndices = new unsigned short[NUMBER_OF_INDICES];

    setupBaseTriangles();
}

RoamMesh::~RoamMesh()
{
    setVertexArray(0);

    delete m_pIndices;
}

void RoamMesh::initGL()
{
    char *version = (char *)glGetString(GL_VERSION);
    char *vendor = (char *)glGetString(GL_VENDOR);
    char *renderer = (char *)glGetString(GL_RENDERER);
    char *extensions = (char *)glGetString(GL_EXTENSIONS);

    if (version)
        cout << "version:  " << version << endl;

    if (vendor)
        cout << "vendor:   " << vendor << endl;

    if (renderer)
        cout << "renderer: " << renderer << endl;

    if (extensions)
        cout << "ext:      " << extensions << endl;

    m_pVertexArray->initGL();

    bGLReady = true;
}

void RoamMesh::render()
{
    if (!bGLReady)
    {
        initGL();
    }

    //update index buffer
    unsigned short index = 0;

    list<ZTriangle *>::iterator iter = m_Triangles.begin();
    while (iter != m_Triangles.end())
    {
        (*iter)->prepareDraw(m_pIndices, index);
        iter++;
    }

    m_pVertexArray->initRender();

    if (bWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(4.0f);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glDrawElements(GL_TRIANGLES, index, GL_UNSIGNED_SHORT, m_pIndices);

    if (bWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glLineWidth(1.0f);
    }

    m_pVertexArray->finishRender();
}

void RoamMesh::setupBaseTriangles()
{
    unsigned short ind[8];

    for (int i = 0; i < 8; ++i)
    {
        ind[i] = m_pVertexArray->getVertex();
    }

    /*
     Base Triangles

       4 - - - - - 5
      /|          /|
     0 + - - - - 1 |
     | |         | |
     | |         | |
     | 6 - - - - + 7
     |/          |/
     2 - - - - - 3
     */

    (*m_pVertexArray)[ind[0]]->setPos(-1.0f, 1.0f, -1.0f);
    (*m_pVertexArray)[ind[1]]->setPos(1.0f, 1.0f, -1.0f);
    (*m_pVertexArray)[ind[2]]->setPos(-1.0f, -1.0f, -1.0f);
    (*m_pVertexArray)[ind[3]]->setPos(1.0f, -1.0f, -1.0f);
    (*m_pVertexArray)[ind[4]]->setPos(-1.0f, 1.0f, 1.0f);
    (*m_pVertexArray)[ind[5]]->setPos(1.0f, 1.0f, 1.0f);
    (*m_pVertexArray)[ind[6]]->setPos(-1.0f, -1.0f, 1.0f);
    (*m_pVertexArray)[ind[7]]->setPos(1.0f, -1.0f, 1.0f);

    (*m_pVertexArray)[ind[0]]->setNormal(-1.0f, 1.0f, -1.0f);
    (*m_pVertexArray)[ind[1]]->setNormal(1.0f, 1.0f, -1.0f);
    (*m_pVertexArray)[ind[2]]->setNormal(-1.0f, -1.0f, -1.0f);
    (*m_pVertexArray)[ind[3]]->setNormal(1.0f, -1.0f, -1.0f);
    (*m_pVertexArray)[ind[4]]->setNormal(-1.0f, 1.0f, 1.0f);
    (*m_pVertexArray)[ind[5]]->setNormal(1.0f, 1.0f, 1.0f);
    (*m_pVertexArray)[ind[6]]->setNormal(-1.0f, -1.0f, 1.0f);
    (*m_pVertexArray)[ind[7]]->setNormal(1.0f, -1.0f, 1.0f);

    ZTriangle *pTri[12];

    //front
    pTri[0] = new ZTriangle(ind[1], ind[0], ind[2], m_pVertexArray);
    pTri[1] = new ZTriangle(ind[1], ind[2], ind[3], m_pVertexArray);

    //back
    pTri[2] = new ZTriangle(ind[4], ind[5], ind[7], m_pVertexArray);
    pTri[3] = new ZTriangle(ind[4], ind[7], ind[6], m_pVertexArray);

    //right
    pTri[4] = new ZTriangle(ind[5], ind[1], ind[3], m_pVertexArray);
    pTri[5] = new ZTriangle(ind[5], ind[3], ind[7], m_pVertexArray);

    //left
    pTri[6] = new ZTriangle(ind[0], ind[4], ind[6], m_pVertexArray);
    pTri[7] = new ZTriangle(ind[0], ind[6], ind[2], m_pVertexArray);

    //top
    pTri[8] = new ZTriangle(ind[5], ind[4], ind[0], m_pVertexArray);
    pTri[9] = new ZTriangle(ind[5], ind[0], ind[1], m_pVertexArray);

    //bottom
    pTri[10] = new ZTriangle(ind[3], ind[2], ind[6], m_pVertexArray);
    pTri[11] = new ZTriangle(ind[3], ind[6], ind[7], m_pVertexArray);


    for (int i = 0; i < 12; ++i)
    {
        m_Triangles.push_back(pTri[i]);
        pTri[i]->updateVertices();
    }

    //now we need to setup all the edge pointers

    //tri 0
    pTri[0]->m_pEdges[0] = pTri[1];
    pTri[0]->m_pEdges[1] = pTri[9];
    pTri[0]->m_pEdges[2] = pTri[7];

    //tri 1
    pTri[1]->m_pEdges[0] = pTri[0];
    pTri[1]->m_pEdges[1] = pTri[4];
    pTri[1]->m_pEdges[2] = pTri[11];

    //tri 2
    pTri[2]->m_pEdges[0] = pTri[3];
    pTri[2]->m_pEdges[1] = pTri[5];
    pTri[2]->m_pEdges[2] = pTri[8];

    //tri 3
    pTri[3]->m_pEdges[0] = pTri[2];
    pTri[3]->m_pEdges[1] = pTri[6];
    pTri[3]->m_pEdges[2] = pTri[11];

    //tri 4
    pTri[4]->m_pEdges[0] = pTri[5];
    pTri[4]->m_pEdges[1] = pTri[1];
    pTri[4]->m_pEdges[2] = pTri[9];

    //tri 5
    pTri[5]->m_pEdges[0] = pTri[4];
    pTri[5]->m_pEdges[1] = pTri[2];
    pTri[5]->m_pEdges[2] = pTri[11];

    //tri 6
    pTri[6]->m_pEdges[0] = pTri[7];
    pTri[6]->m_pEdges[1] = pTri[3];
    pTri[6]->m_pEdges[2] = pTri[8];

    //tri 7
    pTri[7]->m_pEdges[0] = pTri[6];
    pTri[7]->m_pEdges[1] = pTri[0];
    pTri[7]->m_pEdges[2] = pTri[10];

    //tri 8
    pTri[8]->m_pEdges[0] = pTri[9];
    pTri[8]->m_pEdges[1] = pTri[6];
    pTri[8]->m_pEdges[2] = pTri[2];

    //tri 9
    pTri[9]->m_pEdges[0] = pTri[8];
    pTri[9]->m_pEdges[1] = pTri[0];
    pTri[9]->m_pEdges[2] = pTri[4];

    //tri 10
    pTri[10]->m_pEdges[0] = pTri[11];
    pTri[10]->m_pEdges[1] = pTri[7];
    pTri[10]->m_pEdges[2] = pTri[1];

    //tri 11
    pTri[11]->m_pEdges[0] = pTri[10];
    pTri[11]->m_pEdges[1] = pTri[3];
    pTri[11]->m_pEdges[2] = pTri[5];
}

void RoamMesh::setVertexArray(ZVertexArray *newArray)
{
    if (m_pVertexArray != newArray)
    {
        if (m_pVertexArray)
        {
            delete m_pVertexArray;
            m_pVertexArray = 0;
        }

        if (newArray)
        {
            m_pVertexArray = newArray;
        }
    }
}

void RoamMesh::toggleWireframe()
{
    bWireframe = !bWireframe;
}

void RoamMesh::update()
{
    if (m_Triangles.size() < 100)
    {
       (*m_Triangles.begin())->split();
    }
}
