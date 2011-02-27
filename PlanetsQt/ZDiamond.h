#ifndef ZDIAMOND_H
#define ZDIAMOND_H

class ZTriangle;

class ZDiamond
{
public:
    ZDiamond();

    ZTriangle *m_pParent[2];
    ZTriangle *m_pChild[2];

};

#endif // ZDIAMOND_H
