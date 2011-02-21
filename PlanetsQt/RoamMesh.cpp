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

void RoamMesh::Render()
{
    if (!bGLReady)
    {
        initGL();
    }

    //update index buffer
    unsigned short index = 0;

    list<ZTriangle *>::iterator iter = m_BaseTriangles.begin();
    while (iter != m_BaseTriangles.end())
    {
        (*iter)->PrepareDraw(m_pIndices, index);
        iter++;
    }

    m_pVertexArray->initRender();


    glDrawElements(GL_TRIANGLES, index, GL_UNSIGNED_SHORT, m_pIndices);

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
        m_BaseTriangles.push_back(pTri[i]);
        pTri[i]->UpdateVertices();
    }
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
