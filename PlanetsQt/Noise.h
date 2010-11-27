#ifndef _NOISE_
#define _NOISE_

#include <cmath>
using namespace std;

static const float PI	= 3.141592654f;

class Noise
{
public:
    Noise(int seed);

    float fBm(float x, int depth);
    float fBm(float x, float y, int depth);
    float fBm(float x, float y, float z, int depth);

    float fBmWithExtraCalc(float x, float y, int depth);

    int getSeed();

    float noise(float x);
    float noise(float x, float y);
    float noise(float x, float y, float z);

    float noise(int x);
    float noise(int x, int y);
    float noise(int x, int y, int z);

    static float cosineInterpolate(float a, float b, float x)
    {
        float ft = x * PI;
        ft = (1.0f - cos(ft)) * 0.5f;
        return a * (1.0f - ft) + (b * ft);
    }

protected:

private:


    float smoothedNoise(float x);
    float smoothedNoise(float x, float y);

    int m_dwSeed;

};

#endif
