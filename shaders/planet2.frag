#extension GL_EXT_gpu_shader4 : enable

varying vec3 normal;

uniform int	planetSeed;
uniform float planetRadius;

float fBm(in float x, in float y, in float z, in int depth);
float noise(in int x, in int y, in int z);
float noise(in float x, in float y, in float z);
float cosineInterpolate(in float a, in float b, in float x);

void main() 
{	
	float value = fBm(normal.x * planetRadius, normal.y * planetRadius, normal.z * planetRadius, 5);

	gl_FragColor = vec4(value, value, value, 1.0f);
}

float fBm(in float x, in float y, in float z, in int depth)
{
	float fWeight = 1.0;
	float fResult = 0.0;

	for (int i = 0; i < depth; ++i)
	{
		fResult += noise(x, y, z) * fWeight;

		x		*= 2.0;
		y		*= 2.0;
		z		*= 2.0;
		fWeight *= 0.5;
	}

	return fResult;
}

float noise(in float x, in float y, in float z)
{
	int xLo = int(floor(x));
	int xHi = xLo + 1;

	int yLo = int(floor(y));
	int yHi = yLo + 1;

	int zLo = int(floor(z));
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

	float i1 = cosineInterpolate(a, b, fFractPartX);
	float i2 = cosineInterpolate(c, d, fFractPartX);
	float i3 = cosineInterpolate(e, f, fFractPartX);
	float i4 = cosineInterpolate(g, h, fFractPartX);

	float j1 = cosineInterpolate(i1, i2, fFractPartY);
	float j2 = cosineInterpolate(i3, i4, fFractPartY);
	
	return cosineInterpolate(j1, j2, fFractPartZ);
}

float noise(in int x, in int y, in int z)
{
	x = x + (planetSeed * y) + (((planetSeed * 5) << 2) * z) + ((planetSeed * 9) << 3);
	x = (x << 13) ^ x;

	x = (x * (x * x * 57737 + 119849) + 1299791 );
	x = (x & 0x7fffffff);

	return (1.0 - float(x) / 1073741824.0);
}

float cosineInterpolate(in float a, in float b, in float x)
{
	float ft = x * 3.141592654;
	ft = (1.0 - cos(ft)) * 0.5;
	return a * (1.0 - ft) + (b * ft);
}
