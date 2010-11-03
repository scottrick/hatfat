#ifndef _MATRIX_
#define _MATRIX_

#include "Vector3.h"

class Matrix
{
public:
    Matrix();
    ~Matrix()					{};

    void Dump();
    void LoadIdentity();
    void RotateBy(Matrix &rot);
    void SetRotation(Vector3 &vAxis, const float fDegrees);

    float						m[16];
    /*
    MATRIX STORED LIKE THIS (like OpenGL wants them):

    [  m0   m4   m8   m12  ]
    [  m1   m5   m9   m13  ]
    [  m2   m6   m10  m14  ]
    [  m3   m7   m11  m15  ]
    */
protected:


private:

};

#endif
