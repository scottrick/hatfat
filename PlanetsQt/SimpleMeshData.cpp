#include "SimpleMeshData.h"

#include <iostream>
using namespace std;

#include "Noise.h"

#define TEST_NOISE_DIMENSION_SIZE 8.0f
#define VERTEX_STEP 0.1f

#define TEST_NOISE_X_MIN -TEST_NOISE_DIMENSION_SIZE
#define TEST_NOISE_X_MAX TEST_NOISE_DIMENSION_SIZE
#define TEST_NOISE_Y_MIN -TEST_NOISE_DIMENSION_SIZE
#define TEST_NOISE_Y_MAX TEST_NOISE_DIMENSION_SIZE

SimpleMeshData::SimpleMeshData(Noise *pNoise)
{
    m_pNoise = pNoise;

    setupStaticArrays();
    generateMeshForTime(0.0f);
}

SimpleMeshData::~SimpleMeshData()
{
    if (m_pIndices)
    {
        delete m_pIndices;
    }

    if (m_pVertices)
    {
        delete m_pVertices;
    }

    if (m_pColors)
    {
        delete m_pColors;
    }
}


void SimpleMeshData::dump() const
{
    cout << "SimpleMeshData   0x" << this << endl;
    cout << "  # verts   --> " << m_NumberOfVertices << endl;
    cout << "  # index   --> " << m_NumberOfIndices << endl;

    for (int i = 0; i < m_NumberOfVertices; ++i)
    {
        cout << " vertex #" << i << "  (" << m_pVertices[i * 3] << ", " << m_pVertices[i * 3 + 1] << ", " << m_pVertices[i * 3 + 2] << ")" << endl;
    }

    for (int i = 0; i < m_NumberOfIndices; ++i)
    {
        cout << " index  #" << i << " = " << m_pIndices[i] << endl;
    }
}

void SimpleMeshData::generateMeshForTime(float fTime)
{
    float fValue = 0.0f;
    float fBlueCutoff = -0.15f;

    //create some test noise
    for (int y = 0; y < m_NumberInRowY; ++y)
    {
        for (int x = 0; x < m_NumberInRowX; ++x)
        {
            fValue = m_pNoise->fBm(TEST_NOISE_X_MIN + VERTEX_STEP * x, TEST_NOISE_Y_MIN + VERTEX_STEP * y, fTime, 4);
            //m_pVertices[(y * m_NumberInRowY + x) * 3 + 2] = m_pNoise->fBm(TEST_NOISE_X_MIN + VERTEX_STEP * x, TEST_NOISE_Y_MIN + VERTEX_STEP * y, 1);

            if (fValue > 0.9f)
            {
                m_pColors[(y * m_NumberInRowY + x)] = 0xffffffff;
            }
            else if (fValue > fBlueCutoff)
            {
                m_pColors[(y * m_NumberInRowY + x)] = 0xff003399;
            }
            else
            {
                m_pColors[(y * m_NumberInRowY + x)] = 0xffff0000;
            }

            if (fValue < fBlueCutoff)
            {
                m_pVertices[(y * m_NumberInRowY + x) * 3 + 2] = fBlueCutoff;
            }
            else
            {
                fValue = fBlueCutoff + ((fValue - fBlueCutoff) * 0.70f);
                m_pVertices[(y * m_NumberInRowY + x) * 3 + 2] = fValue;
            }
        }
    }
}

void SimpleMeshData::setupStaticArrays()
{
    //allocate the vertices array
    m_NumberInRowX = (int) ((TEST_NOISE_X_MAX - TEST_NOISE_X_MIN) / VERTEX_STEP) + 1;
    m_NumberInRowY = (int) ((TEST_NOISE_Y_MAX - TEST_NOISE_Y_MIN) / VERTEX_STEP) + 1;

    m_NumberOfVertices = m_NumberInRowX * m_NumberInRowY;
    m_NumberOfIndices = (m_NumberInRowX - 1) * (m_NumberInRowY - 1) * 6; //2 triangles for each square, so 6 indices

    m_pVertices = new float[m_NumberOfVertices * 3];
    m_pIndices = new int[m_NumberOfIndices];
    m_pColors = new int[m_NumberOfVertices];

    //some test colors
    for (int i = 0; i < m_NumberOfVertices; ++i)
    {
        m_pColors[i] = 0xffff00ff;
    }

    //create some test indices
    for (int y = 0; y < (m_NumberInRowY - 1); ++y)
    {
        for (int x = 0; x < (m_NumberInRowY - 1); ++x)
        {
            //verts for drawaing GL_TRIANGLES
            //m_pIndices[(y * (m_NumberInRowY - 1) + x) * 6 + 0] = (y * numberInRowY) + x;
            //m_pIndices[(y * (m_NumberInRowY - 1) + x) * 6 + 1] = (y * numberInRowY) + x + 1;
            //m_pIndices[(y * (m_NumberInRowY - 1) + x) * 6 + 2] = ((y + 1) * numberInRowY) + x + 1;
            //m_pIndices[(y * (m_NumberInRowY - 1) + x) * 6 + 3] = (y * numberInRowY) + x;
            //m_pIndices[(y * (m_NumberInRowY - 1) + x) * 6 + 4] = ((y + 1) * numberInRowY) + x + 1;
            //m_pIndices[(y * (m_NumberInRowY - 1) + x) * 6 + 5] = ((y + 1) * numberInRowY) + x;

            //verts for drawing wireframe triangles
            m_pIndices[(y * (m_NumberInRowY - 1) + x) * 6 + 0] = (y * m_NumberInRowY) + x;
            m_pIndices[(y * (m_NumberInRowY - 1) + x) * 6 + 1] = (y * m_NumberInRowY) + x + 1;
            m_pIndices[(y * (m_NumberInRowY - 1) + x) * 6 + 2] = (y * m_NumberInRowY) + x + 1;
            m_pIndices[(y * (m_NumberInRowY - 1) + x) * 6 + 3] = ((y + 1) * m_NumberInRowY) + x;
            m_pIndices[(y * (m_NumberInRowY - 1) + x) * 6 + 4] = ((y + 1) * m_NumberInRowY) + x;
            m_pIndices[(y * (m_NumberInRowY - 1) + x) * 6 + 5] = (y * m_NumberInRowY) + x;
        }
    }

    //set the X,Y values since they never hcange, and just give the Z values some default
    for (int y = 0; y < m_NumberInRowY; ++y)
    {
        for (int x = 0; x < m_NumberInRowX; ++x)
        {
            m_pVertices[(y * m_NumberInRowY + x) * 3 + 0] = TEST_NOISE_X_MIN + VERTEX_STEP * x;
            m_pVertices[(y * m_NumberInRowY + x) * 3 + 1] = TEST_NOISE_Y_MIN + VERTEX_STEP * y;
            m_pVertices[(y * m_NumberInRowY + x) * 3 + 2] = m_pNoise->fBm(TEST_NOISE_X_MIN + VERTEX_STEP * x, TEST_NOISE_Y_MIN + VERTEX_STEP * y, 0.0f, 1);
        }
    }
}
