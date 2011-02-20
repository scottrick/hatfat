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
