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

    InitTest();
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

//    //setup the index array
//    glGenBuffers(1, &indexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUMBER_OF_INDICES * sizeof(unsigned short), m_pIndices, GL_STREAM_DRAW);

    bGLReady = true;
}

void RoamMesh::InitTest()
{
    unsigned short indices[4];
    indices[0] = m_pVertexArray->getVertex();
    indices[1] = m_pVertexArray->getVertex();
    indices[2] = m_pVertexArray->getVertex();
    indices[3] = m_pVertexArray->getVertex();

    (*m_pVertexArray)[0]->m_vPos.Set(-1.0f, 1.0f, 0.1f);
    (*m_pVertexArray)[1]->m_vPos.Set(-1.0f, -1.0f, 0.1f);
    (*m_pVertexArray)[2]->m_vPos.Set(1.0f, 1.0f, 0.1f);
    (*m_pVertexArray)[3]->m_vPos.Set(1.0f, -1.0f, 0.1f);

    m_pVertexArray->updateVertex(indices[0]); //need to hook this into the triangle somehow?
    m_pVertexArray->updateVertex(indices[1]);
    m_pVertexArray->updateVertex(indices[2]);
    m_pVertexArray->updateVertex(indices[3]);

    m_pTestTriangle = new ZTriangle(indices[0], indices[1], indices[2]);
    m_pTriTwo = new ZTriangle(indices[2], indices[1], indices[3]);
}

void RoamMesh::Render()
{
    if (!bGLReady)
    {
        initGL();
    }

    //update index buffer
    unsigned short index = 0;
    m_pTestTriangle->PrepareDraw(m_pIndices, index);
    m_pTriTwo->PrepareDraw(m_pIndices, index);

    m_pVertexArray->initRender();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, m_pIndices);

    m_pVertexArray->finishRender();
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
