#ifndef ZTRIANGLE_H
#define ZTRIANGLE_H

class ZDiamond;
class ZVertexArray;

class ZTriangle
{
public:
    ZTriangle(unsigned short v1, unsigned short v2, unsigned short v3, ZVertexArray *array);

    ZVertexArray *m_pVertexArray;

    unsigned short m_Vertex[3]; //indices into the vertex array, for the vertices

    void dump();
    bool isDiamondReady(); //returns true when its 'diamond partner' exists and is at the same split level
    void prepareDraw(unsigned short *array, unsigned short &index);
    void split();
    void updateEdge(ZTriangle *pOldEdge, ZTriangle *pNewEdge);
    void updateVertices();

    ZTriangle *m_pParent; //parent triangle
    ZDiamond *m_pDiamond; //diamond, if its in any

    ZTriangle *m_pEdges[3]; //other triangles adjacent to this one

    //split level is used to quickly determine if two triangles are on the same level of the 'tree,' and have been split the same number of times.
    int m_SplitLevel;
    //Diamond Edge Index is used to tell which edge triangle this triangle will eventually be in a diamond with
    short m_DiamondEdgeIndex;

//    CROAMTriangle *m_pEdge[3]; // Pointers to edge neighbors
//    CROAMTriangle *m_pParent; // Pointer to the parent triangle
//    CROAMDiamond *m_pDiamond; // Set if this triangle is in a diamond

//    // Split priority members
//    CVector m_vMidpoint; // The midpoint of the longest edge
//    float m_fOffset; // The offset in height
//    float m_fLength; // The length of the longest edge
//    unsigned char m_nFlags;

//    float GetPriority(CVector &vPosition, CVector &vHeading, float fHorizon);
//    void Draw(GLenum nMode, unsigned short *nArray, unsigned short &nIndex);
};

#endif // ZTRIANGLE_H
