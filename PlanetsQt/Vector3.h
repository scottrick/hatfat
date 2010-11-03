#ifndef _VECTOR_3_
#define _VECTOR_3_

class Vector3
{
public:
    Vector3();
    Vector3(float newX, float newY, float newZ);

    float x;
    float y;
    float z;

    void Normalize();

};

#endif
