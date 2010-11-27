#include "Noise.h"

#include <cmath>
#include <iostream>
using namespace std;

Noise::Noise(int seed)
{
    m_dwSeed = seed;
}

float Noise::fBm(float x, int depth)
{
    float fWeight = 1.0f;
    float fResult = 0.0f;

    for (int i = 0; i < depth; ++i)
    {
        fResult += noise(x * fWeight);

        x		*= 2.0f;
        fWeight *= 0.5f;
    }

    return fResult;
}

float Noise::fBm(float x, float y, int depth)
{
    float fWeight = 1.0f;
    float fResult = 0.0f;

    for (int i = 0; i < depth; ++i)
    {
        fResult += noise(x, y) * fWeight;

        x		*= 2.0f;
        y		*= 2.0f;
        fWeight *= 0.5f;
    }

    return fResult;
}

float Noise::fBm(float x, float y, float z, int depth)
{
    float fWeight = 1.0f;
    float fResult = 0.0f;

    for (int i = 0; i < depth; ++i)
    {
        fResult += noise(x, y, z) * fWeight;

        x		*= 2.0f;
        y		*= 2.0f;
        z		*= 2.0f;
        fWeight *= 0.5f;
    }

    return fResult;
}

float Noise::fBmWithExtraCalc(float x, float y, int depth)
{
    float fValue = fBm(x, y, depth);

    return fValue * fValue;
}

int Noise::getSeed()
{
    return m_dwSeed;
}

float Noise::noise(float x)
{
    int intA = (int)floor(x);
    int intB = intA + 1;

    float a = noise(intA);
    float b = noise(intB);

    float fFractPart = x - floor(x);

    return Noise::cosineInterpolate(a, b, fFractPart);
}

float Noise::noise(float x, float y)
{
    int xLo = (int) floor(x); //x-value stuff
    int xHi = xLo + 1;

    int yLo = (int) floor(y); //y-value stuff
    int yHi = yLo + 1;

    float a = noise(xLo, yLo);
    float b = noise(xHi, yLo);
    float c = noise(xLo, yHi);
    float d = noise(xHi, yHi);

    float fFractPartX = x - floor(x);
    float fFractPartY = y - floor(y);

    float i1 = Noise::cosineInterpolate(a, b, fFractPartX);
    float i2 = Noise::cosineInterpolate(c, d, fFractPartX);

    return Noise::cosineInterpolate(i1, i2, fFractPartY);
}

float Noise::noise(float x, float y, float z)
{
    int xLo = (int) floor(x); //x-value stuff
    int xHi = xLo + 1;

    int yLo = (int) floor(y); //y-value stuff
    int yHi = yLo + 1;

    int zLo = (int) floor(z);
    int zHi = zLo + 1;

    float a = noise(xLo, yLo, zLo);
    float b = noise(xHi, yLo, zLo);
    float c = noise(xLo, yHi, zLo);
    float d = noise(xHi, yHi, zLo);

    float e = noise(xLo, yLo, zHi);
    float f = noise(xHi, yLo, zHi);
    float g = noise(xLo, yHi, zHi);
    float h = noise(xHi, yHi, zHi);

    float fFractPartX = x - floor(x);
    float fFractPartY = y - floor(y);
    float fFractPartZ = z - floor(z);

    float i1 = Noise::cosineInterpolate(a, b, fFractPartX);
    float i2 = Noise::cosineInterpolate(c, d, fFractPartX);
    float i3 = Noise::cosineInterpolate(e, f, fFractPartX);
    float i4 = Noise::cosineInterpolate(g, h, fFractPartX);

    float j1 = Noise::cosineInterpolate(i1, i2, fFractPartY);
    float j2 = Noise::cosineInterpolate(i3, i4, fFractPartY);

    return Noise::cosineInterpolate(j1, j2, fFractPartZ);
}

float Noise::noise(int x)
{
    x = x + m_dwSeed;
    x = (x << 13) ^ x;

    return (1.0f - ((x * (x * x * 57737 + 119849) + 1299791 ) & 0x7fffffff) / 1073741824.0f);
}

float Noise::noise(int x, int y)
{
    //	x = (x + y) * m_dwSeed;
    x = x + (m_dwSeed * y) + ((m_dwSeed * 7 ) << 2);
    x = (x << 13) ^ x;

    return (1.0f - ((x * (x * x * 57737 + 119849) + 1299791 ) & 0x7fffffff) / 1073741824.0f);
}

float Noise::noise(int x, int y, int z)
{
    x = x + (m_dwSeed * y) + (((m_dwSeed * 5) << 2) * z) + ((m_dwSeed * 9) << 3);
    x = (x << 13) ^ x;

    return (1.0f - ((x * (x * x * 57737 + 119849) + 1299791 ) & 0x7fffffff) / 1073741824.0f);
}
