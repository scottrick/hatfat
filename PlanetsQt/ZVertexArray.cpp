#include "ZVertexArray.h"

#include <iostream>
using namespace std;

ZVertexArray::ZVertexArray()
{
    m_StackPosition = 0;

    m_pBuffer = new ZVertex[VERTEX_ARRAY_SIZE];
    m_pStack = new unsigned short[VERTEX_ARRAY_SIZE];
    m_pUpdated = new unsigned char[VERTEX_ARRAY_SIZE];

    for (unsigned short i = 0; i < VERTEX_ARRAY_SIZE; ++i)
    {
        m_pStack[i] = i;
        m_pUpdated[i] = 0;
    }
}

ZVertexArray::~ZVertexArray()
{
    delete m_pBuffer;
    delete m_pStack;
    delete m_pUpdated;
}

unsigned short ZVertexArray::getVertex()
{
    return m_pStack[m_StackPosition++];
}

void ZVertexArray::releaseVertex(unsigned short index)
{
    m_StackPosition--;
    m_pStack[m_StackPosition] = index;
}

void ZVertexArray::updateVertex(unsigned short index)
{
    m_pUpdated[index] = 1;
}

void ZVertexArray::initGL()
{
    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, VERTEX_ARRAY_SIZE * sizeof(ZVertex), m_pBuffer, GL_STREAM_DRAW);

    int bufferSize = 0;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

//    cout << "bufferSize " << bufferSize << "    real " << (VERTEX_ARRAY_SIZE * sizeof(ZVertex)) << endl;

    const char *error = GLeeGetErrorString();
    if (*error != '\0')
    {
        cout << "GL ERROR: " << error << endl;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ZVertexArray::initRender()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(ZVertex), 0);

    glEnableClientState(GL_NORMAL_ARRAY);

    //last param is offset into the buffer.  Since the normals are after the position information,
    //its just the size of the position data
    glNormalPointer(GL_FLOAT, sizeof(ZVertex), (void *)sizeof(VECTOR3));

    ZVertex *pVideoBuffer = (ZVertex *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    //Update any vertices that have changed!
    for (unsigned short i = 0; i < VERTEX_ARRAY_SIZE; ++i)
    {
        if (m_pUpdated[i])
        {
            pVideoBuffer[i] = m_pBuffer[i];
            m_pUpdated[i] = 0;

//            cout << "updated (" << i << ") ";
//            m_pBuffer[i].dump();
        }
    }

    GLboolean unmap = glUnmapBuffer(GL_ARRAY_BUFFER);

    if (unmap == GL_FALSE)
    {
        cout << "failed to unmap!" << endl;
    }
}

void ZVertexArray::finishRender()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}
