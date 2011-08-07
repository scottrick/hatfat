#include "ZDiamond.h"

#include "RoamMesh.h"
#include "ZTriangle.h"
#include "ZVertex.h"
#include "ZVertexArray.h"

#include <cassert>
#include <iostream>
using namespace std;

ZDiamond::ZDiamond()
{
    m_pParent[0] = 0;
    m_pParent[1] = 0;
    m_pChild[0] = 0;
    m_pChild[1] = 0;
    m_pChild[2] = 0;
    m_pChild[3] = 0;
}

void ZDiamond::split()
{
    assert(m_pParent[0]->m_DiamondEdgeIndex >= 0 && m_pParent[0]->m_DiamondEdgeIndex < 3);
    assert(m_pParent[0]->m_SplitLevel >= 0);
    assert(m_pParent[1]->m_DiamondEdgeIndex >= 0 && m_pParent[1]->m_DiamondEdgeIndex < 3);
    assert(m_pParent[1]->m_SplitLevel >= 0);

    int v1 = -1;
    int v2 = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (m_pParent[0]->m_Vertex[i] == m_pParent[1]->m_Vertex[j])
            { //looking for the two common vertices
                if (v1 < 0)
                {
                    v1 = m_pParent[0]->m_Vertex[i];
                }
                else if (v2 < 0)
                {
                    v2 = m_pParent[0]->m_Vertex[i];
                }
            }
        }
    }

    /*

        parent[0] / parent[1]

           1/? - - - - - - - 0/0
            | *             * |
            |   *    c2   *   |
            |      *   *      |
            |  c1    M    c3  |
            |      *   *      |
            |   *    c4   *   |
            | *             * |
           2/1 - - - - - - - ?/2

     */

    ZVertexArray *pVertexArray = m_pParent[0]->m_pVertexArray;

    ZVertex *pVertexOne = (*pVertexArray)[v1];
    ZVertex *pVertexTwo = (*pVertexArray)[v2];

    //make the new midpoing vertex
    unsigned short m = pVertexArray->getVertex();

    ZVertex *pMidpoint = (*pVertexArray)[m];
    pMidpoint->makeMidpoint(pVertexOne, pVertexTwo);
    pVertexArray->updateVertex(m);

    //make the four children!
//    ZTriangle *c1 = new ZTriangle(m_pParent[0]->m_Vertex[2], m, m_pParent[0]->m_Vertex[1], pVertexArray);
    ZTriangle *c1 = new ZTriangle(m_pParent[0]->m_Vertex[1], m_pParent[0]->m_Vertex[2], m, pVertexArray);

//    ZTriangle *c2 = new ZTriangle(m_pParent[0]->m_Vertex[1], m, m_pParent[0]->m_Vertex[0], pVertexArray);
    ZTriangle *c2 = new ZTriangle(m_pParent[0]->m_Vertex[0], m_pParent[0]->m_Vertex[1], m, pVertexArray);

    ZTriangle *c3 = new ZTriangle(m_pParent[1]->m_Vertex[0], m, m_pParent[1]->m_Vertex[2], pVertexArray);
    ZTriangle *c4 = new ZTriangle(m_pParent[1]->m_Vertex[2], m, m_pParent[1]->m_Vertex[1], pVertexArray);

    c1->m_SplitLevel = m_pParent[0]->m_SplitLevel + 1;
    c2->m_SplitLevel = m_pParent[0]->m_SplitLevel + 1;
    c3->m_SplitLevel = m_pParent[1]->m_SplitLevel + 1;
    c4->m_SplitLevel = m_pParent[1]->m_SplitLevel + 1;
    c1->m_DiamondEdgeIndex = 0;
    c2->m_DiamondEdgeIndex = 0;
    c3->m_DiamondEdgeIndex = 2;
    c4->m_DiamondEdgeIndex = 2;

    //setup the edges on the new triangles.  See RoamMesh.cpp for more information about which edge is which.
    c1->m_pEdges[0] = m_pParent[0]->m_pEdges[1];
    c1->m_pEdges[1] = c4;
    c1->m_pEdges[2] = c2;

    c2->m_pEdges[0] = m_pParent[0]->m_pEdges[0];
    c2->m_pEdges[1] = c1;
    c2->m_pEdges[2] = c3;

    c3->m_pEdges[0] = c2;
    c3->m_pEdges[1] = c4;
    c3->m_pEdges[2] = m_pParent[1]->m_pEdges[2];

    c4->m_pEdges[0] = c3;
    c4->m_pEdges[1] = c1;
    c4->m_pEdges[2] = m_pParent[1]->m_pEdges[1];

    c1->m_pParent = m_pParent[0];
    c2->m_pParent = m_pParent[0];
    c3->m_pParent = m_pParent[1];
    c4->m_pParent = m_pParent[1];

    //update the parent's edge triangles edges... so they point to the new children triangles.  yes that was a mouth full
    m_pParent[0]->m_pEdges[0]->updateEdge(m_pParent[0], c2);
    m_pParent[0]->m_pEdges[1]->updateEdge(m_pParent[0], c1);
    m_pParent[1]->m_pEdges[1]->updateEdge(m_pParent[1], c4);
    m_pParent[1]->m_pEdges[2]->updateEdge(m_pParent[1], c3);

    //check the new triangles and see if they should be part of a diamond
    if (c1->isDiamondReady()) {
        this->m_pMesh->makeNewDiamondForTriangles(c1->m_pEdges[c1->m_DiamondEdgeIndex], c1);
    }
    if (c2->isDiamondReady()) {
        this->m_pMesh->makeNewDiamondForTriangles(c2->m_pEdges[c2->m_DiamondEdgeIndex], c2);
    }
    if (c3->isDiamondReady()) {
        this->m_pMesh->makeNewDiamondForTriangles(c3, c3->m_pEdges[c3->m_DiamondEdgeIndex]);
    }
    if (c4->isDiamondReady()) {
        this->m_pMesh->makeNewDiamondForTriangles(c4, c4->m_pEdges[c4->m_DiamondEdgeIndex]);
    }

    m_pMesh->addTriangle(c1);
    m_pMesh->addTriangle(c2);
    m_pMesh->addTriangle(c3);
    m_pMesh->addTriangle(c4);

    m_pMesh->removeTriangle(m_pParent[0]);
    m_pMesh->removeTriangle(m_pParent[1]);

    m_pMesh->removeDiamond(this);
}
