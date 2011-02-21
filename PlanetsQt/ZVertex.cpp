#include "ZVertex.h"

#include <iostream>
using namespace std;


ZVertex::ZVertex()
{

}

void ZVertex::dump()
{
    cout << "ZVertex 0x" << hex << this << dec << "  (" << m_vPos.x << ", " << m_vPos.y << ", " << m_vPos.z << ")" << endl;
}

void ZVertex::setNormal(const float &x, const float &y, const float &z)
{
    m_vNrm.Set(x, y, z);
    NormalizeVECTOR3(m_vNrm);
}

void ZVertex::setPos(const float &x, const float &y, const float &z)
{
    m_vPos.Set(x, y, z);
}
