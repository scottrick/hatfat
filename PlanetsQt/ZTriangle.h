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

    void prepareDraw(unsigned short *array, unsigned short &index);
    void split();
    void updateVertices();

    ZTriangle *m_pParent; //parent triangle
    ZDiamond *m_pDiamond; //diamond, if its in any

    ZTriangle *m_pEdges[3]; //other triangles adjacent to this one


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
