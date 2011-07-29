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

//set ourselves to be the midpoint between the start and the end
void ZVertex::makeMidpoint(ZVertex *pStart, ZVertex *pEnd)
{
    VECTOR3 pos[2];
    pos[0] = pStart->getPosition();
    pos[1] = pEnd->getPosition();

    VECTOR3 nrm[2];
    nrm[0] = pStart->getNormal();
    nrm[1] = pEnd->getNormal();

    cout << "makeMidpoint!" << endl;
    cout << "(1) ";
    pStart->dump();
    cout << "(2) ";
    pEnd->dump();

    //just naively assume its an average for now...
    this->setPos((pos[0].x + pos[1].x) / 2.0f, (pos[0].y + pos[1].y) / 2.0f, (pos[0].z + pos[1].z) / 2.0f);
    this->setNormal((nrm[0].x + nrm[1].x) / 2.0f, (nrm[0].y + nrm[1].y) / 2.0f, (nrm[0].z + nrm[1].z) / 2.0f);

    cout << "(!) ";
    this->dump();
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
