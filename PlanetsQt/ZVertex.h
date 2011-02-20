#ifndef ZVERTEX_H
#define ZVERTEX_H

#include "def.h"

class ZVertexArray;

class ZVertex
{
public:
    ZVertex();

//    static ZVertexArray array;

    VECTOR3 m_vPos; //position
    VECTOR3 m_vNrm; //normal

//    float   m_fTexCoord[4]; //two pairs of texture coordinates
    void dump();
};

#endif // ZVERTEX_H
