#ifndef ZDIAMOND_H
#define ZDIAMOND_H

class RoamMesh;
class ZTriangle;

class ZDiamond
{
public:
    ZDiamond();

    RoamMesh *m_pMesh;
    ZTriangle *m_pParent[2];
    ZTriangle *m_pChild[4];

    void split();

};

#endif // ZDIAMOND_H
