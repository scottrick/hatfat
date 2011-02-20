#include "ZTriangle.h"

ZTriangle::ZTriangle(unsigned short v1, unsigned short v2, unsigned short v3)
{
    m_Vertex[0] = v1;
    m_Vertex[1] = v2;
    m_Vertex[2] = v3;
}

void ZTriangle::PrepareDraw(unsigned short *array, unsigned short &index)
{
    array[index++] = m_Vertex[0];
    array[index++] = m_Vertex[1];
    array[index++] = m_Vertex[2];
}
