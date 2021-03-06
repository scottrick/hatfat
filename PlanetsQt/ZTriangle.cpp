#include "ZTriangle.h"

#include "ZDiamond.h"
#include "ZVertexArray.h"

#include <iostream>
using namespace std;

ZTriangle::ZTriangle(unsigned short v1, unsigned short v2, unsigned short v3, ZVertexArray *array)
    : m_SplitLevel(-1), m_DiamondEdgeIndex(-1)
{
    m_Vertex[0] = v1;
    m_Vertex[1] = v2;
    m_Vertex[2] = v3;
    m_pVertexArray = array;

    m_pParent = 0;
    m_pDiamond = 0;
    m_pEdges[0] = 0;
    m_pEdges[1] = 0;
    m_pEdges[2] = 0;
}

void ZTriangle::dump()
{
    cout << "ZTriangle " << hex << this << dec << endl;
    cout << "  (0) ";
    m_pVertexArray->m_pBuffer[m_Vertex[0]].dump();
    cout << "  (1) ";
    m_pVertexArray->m_pBuffer[m_Vertex[1]].dump();
    cout << "  (2) ";
    m_pVertexArray->m_pBuffer[m_Vertex[2]].dump();
}

bool ZTriangle::isDiamondReady()
{
//    cout << "isDiamondReady " << this->m_pEdges[this->m_DiamondEdgeIndex]->m_SplitLevel << ", " << this->m_SplitLevel << endl;
    if (this->m_pEdges[this->m_DiamondEdgeIndex]->m_SplitLevel == this->m_SplitLevel)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ZTriangle::prepareDraw(unsigned short *array, unsigned short &index)
{
    array[index++] = m_Vertex[0];
    array[index++] = m_Vertex[1];
    array[index++] = m_Vertex[2];
}

void ZTriangle::split()
{
    if (m_pDiamond)
    {
        cout << "splitting " << hex << this << dec << endl;
        m_pDiamond->split();
    }
    else
    {
        cout << "unable to split, no diamond!" << endl;
    }
}

void ZTriangle::updateEdge(ZTriangle *pOldEdge, ZTriangle *pNewEdge)
{
    //one of the edges MUST be a match, or we screwed something up
    assert(m_pEdges[0] == pOldEdge || m_pEdges[1] == pOldEdge || m_pEdges[2] == pOldEdge);

    if (m_pEdges[0] == pOldEdge)
    {
        m_pEdges[0] = pNewEdge;
    }
    else if (m_pEdges[1] == pOldEdge)
    {
        m_pEdges[1] = pNewEdge;
    }
    else if (m_pEdges[2] == pOldEdge)
    {
        m_pEdges[2] = pNewEdge;
    }
}

void ZTriangle::updateVertices()
{
    m_pVertexArray->updateVertex(m_Vertex[0]);
    m_pVertexArray->updateVertex(m_Vertex[1]);
    m_pVertexArray->updateVertex(m_Vertex[2]);
}
