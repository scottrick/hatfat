#include "Vector3.h"

#include <cmath>
#include <iostream>
using namespace std;

Vector3::Vector3()
    : x(0.0f), y(0.0f), z(0.0f)
{

}

Vector3::Vector3(float newX, float newY, float newZ)
    : x(newX), y(newY), z(newZ)
{

}

void Vector3::Dump()
{
    cout << "Vector3  0x" << hex << this << dec << " (" << x << ", " << y << ", " << z << ")" << endl;
}

void Vector3::Normalize()
{
    float xSquared = x * x;
    float ySquared = y * y;
    float zSquared = z * z;

    float denominator = 1.0f / sqrt(xSquared + ySquared + zSquared);

    x = x * denominator;
    y = y * denominator;
    z = z * denominator;
}
