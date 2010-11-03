#include "Matrix.h"

#include <cmath>
#include <iostream>
using namespace std;

Matrix::Matrix()
{
    LoadIdentity();
}

void Matrix::Dump()
{
    cout << "Matrix 0x" << this << endl;
    cout << "[ " << m[0] << "  " << m[1] << "  " << m[2] << "  " << m[3] << "  ]" << endl;
    cout << "[ " << m[4] << "  " << m[5] << "  " << m[6] << "  " << m[7] << "  ]" << endl;
    cout << "[ " << m[8] << "  " << m[9] << "  " << m[10] << "  " << m[11] << "  ]" << endl;
    cout << "[ " << m[12] << "  " << m[13] << "  " << m[14] << "  " << m[15] << "  ]" << endl;
}

void Matrix::LoadIdentity()
{
    m[0]	= 1.0f;
    m[1]	= 0.0f;
    m[2]	= 0.0f;
    m[3]	= 0.0f;
    m[4]	= 0.0f;
    m[5]	= 1.0f;
    m[6]	= 0.0f;
    m[7]	= 0.0f;
    m[8]	= 0.0f;
    m[9]	= 0.0f;
    m[10]	= 1.0f;
    m[11]	= 0.0f;
    m[12]	= 0.0f;
    m[13]	= 0.0f;
    m[14]	= 0.0f;
    m[15]	= 1.0f;
}

void Matrix::RotateBy(Matrix &rot)
{
    //result = rot * this

    Matrix result;

    result.m[0]	= m[0] * rot.m[0] + m[1] * rot.m[4] + m[2] * rot.m[8] + m[3] * rot.m[12];
    result.m[1]	= m[0] * rot.m[1] + m[1] * rot.m[5] + m[2] * rot.m[9] + m[3] * rot.m[13];
    result.m[2]	= m[0] * rot.m[2] + m[1] * rot.m[6] + m[2] * rot.m[10] + m[3] * rot.m[14];
    result.m[3]	= m[0] * rot.m[3] + m[1] * rot.m[7] + m[2] * rot.m[11] + m[3] * rot.m[15];

    result.m[4]	= m[4] * rot.m[0] + m[5] * rot.m[4] + m[6] * rot.m[8] + m[7] * rot.m[12];
    result.m[5]	= m[4] * rot.m[1] + m[5] * rot.m[5] + m[6] * rot.m[9] + m[7] * rot.m[13];
    result.m[6]	= m[4] * rot.m[2] + m[5] * rot.m[6] + m[6] * rot.m[10] + m[7] * rot.m[14];
    result.m[7]	= m[4] * rot.m[3] + m[5] * rot.m[7] + m[6] * rot.m[11] + m[7] * rot.m[15];

    result.m[8]		= m[8] * rot.m[0] + m[9] * rot.m[4] + m[10] * rot.m[8] + m[11] * rot.m[12];
    result.m[9]		= m[8] * rot.m[1] + m[9] * rot.m[5] + m[10] * rot.m[9] + m[11] * rot.m[13];
    result.m[10]	= m[8] * rot.m[2] + m[9] * rot.m[6] + m[10] * rot.m[10] + m[11] * rot.m[14];
    result.m[11]	= m[8] * rot.m[3] + m[9] * rot.m[7] + m[10] * rot.m[11] + m[11] * rot.m[15];

    result.m[12]	= m[12] * rot.m[0] + m[13] * rot.m[4] + m[14] * rot.m[8] + m[15] * rot.m[12];
    result.m[13]	= m[12] * rot.m[1] + m[13] * rot.m[5] + m[14] * rot.m[9] + m[15] * rot.m[13];
    result.m[14]	= m[12] * rot.m[2] + m[13] * rot.m[6] + m[14] * rot.m[10] + m[15] * rot.m[14];
    result.m[15]	= m[12] * rot.m[3] + m[13] * rot.m[7] + m[14] * rot.m[11] + m[15] * rot.m[15];

    m[0]	= result.m[0];
    m[1]	= result.m[1];
    m[2]	= result.m[2];
    m[3]	= result.m[3];
    m[4]	= result.m[4];
    m[5]	= result.m[5];
    m[6]	= result.m[6];
    m[7]	= result.m[7];
    m[8]	= result.m[8];
    m[9]	= result.m[9];
    m[10]	= result.m[10];
    m[11]	= result.m[11];
    m[12]	= result.m[12];
    m[13]	= result.m[13];
    m[14]	= result.m[14];
    m[15]	= result.m[15];
}

void Matrix::SetRotation(Vector3 &vAxis, const float fDegrees)
{
    float fRadians = fDegrees * 3.141592654f / 180.0f;

    float c = cos(fRadians);
    float s = sin(fRadians);
    float t = 1.0f - c;

    vAxis.Normalize();

    m[0]	= t * vAxis.x * vAxis.x + c;
    m[1]	= t * vAxis.x * vAxis.y - s * vAxis.z;
    m[2]	= t * vAxis.x * vAxis.z + s * vAxis.y;
    m[3]	= 0.0f;

    m[4]	= t * vAxis.x * vAxis.y + s * vAxis.z;
    m[5]	= t * vAxis.y * vAxis.y + c;
    m[6]	= t * vAxis.y * vAxis.z - s * vAxis.x;
    m[7]	= 0.0f;

    m[8]	= t * vAxis.x * vAxis.z - s * vAxis.y;
    m[9]	= t * vAxis.y * vAxis.z + s * vAxis.x;
    m[10]	= t * vAxis.z * vAxis.z + c;
    m[11]	= 0.0f;

    m[12]	= 0.0f;
    m[13]	= 0.0f;
    m[14]	= 0.0f;
    m[15]	= 1.0f;
}
