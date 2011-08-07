#include "ZDiamond.h"

#include "RoamMesh.h"
#include "ZTriangle.h"
#include "ZVertex.h"
#include "ZVertexArray.h"

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
    ZTriangle *c1 = new ZTriangle(m_pParent[0]->m_Vertex[2], m, m_pParent[0]->m_Vertex[1], pVertexArray);
    ZTriangle *c2 = new ZTriangle(m_pParent[0]->m_Vertex[1], m, m_pParent[0]->m_Vertex[0], pVertexArray);
    ZTriangle *c3 = new ZTriangle(m_pParent[0]->m_Vertex[0], m, m_pParent[1]->m_Vertex[2], pVertexArray);
    ZTriangle *c4 = new ZTriangle(m_pParent[1]->m_Vertex[2], m, m_pParent[0]->m_Vertex[2], pVertexArray);

//    c1->m_pDiamond = this;
//    c2->m_pDiamond = this;
//    c3->m_pDiamond = this;
//    c4->m_pDiamond = this;

    c1->m_pParent = m_pParent[0];
    c2->m_pParent = m_pParent[0];
    c3->m_pParent = m_pParent[1];
    c4->m_pParent = m_pParent[1];

    m_pMesh->addTriangle(c1);
    m_pMesh->addTriangle(c2);
    m_pMesh->addTriangle(c3);
    m_pMesh->addTriangle(c4);

    m_pMesh->removeTriangle(m_pParent[0]);
    m_pMesh->removeTriangle(m_pParent[1]);

    m_pMesh->removeDiamond(this);
}
