#ifndef ZVERTEX_H
#define ZVERTEX_H

#include "def.h"

class ZVertexArray;

class ZVertex
{
public:
    ZVertex();

    void setPos(const float &x, const float &y, const float &z);
    void setNormal(const float &x, const float &y, const float &z);
    void dump();

    VECTOR3 getPosition() { return m_vPos; }
    VECTOR3 getNormal() { return m_vNrm; }

    void makeMidpoint(ZVertex *pStart, ZVertex *pEnd);

private:
    VECTOR3 m_vPos; //position
    VECTOR3 m_vNrm; //normal
//    float   m_fTexCoord[4]; //two pairs of texture coordinates
};

#endif // ZVERTEX_H
