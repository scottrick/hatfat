varying vec3 normal;
varying float intensity;
	
void main()
{
	float maxIntensity = gl_Color.r * 100.0;

	float xSquaredPlusYSquared = gl_Vertex.x * gl_Vertex.x + gl_Vertex.y * gl_Vertex.y;
	float ySquared = gl_Vertex.y * gl_Vertex.y;
	float zSquared = gl_Vertex.z * gl_Vertex.z;

	intensity = xSquaredPlusYSquared / (xSquaredPlusYSquared + zSquared);
	//intensity = 1.0 - (intensity / maxIntensity);
	//intensity = intensity * (xSquaredPlusYSquared + zSquared) / maxIntensity * maxIntensity;

	intensity = intensity * ((maxIntensity * maxIntensity) - (xSquaredPlusYSquared + zSquared));

	//intensity =	1.0 - ((gl_Vertex.x * gl_Vertex.x) + (gl_Vertex.y * gl_Vertex.y)) / (maxIntensity * maxIntensity);

	intensity = intensity * 0.03;
	
	/*
	if (intensity > 0.9) {
		intensity = intensity * 0.03;
	}
	else if (intensity > 0.7) {
		intensity = intensity * 0.03;
	}
	else if (intensity > 0.5) {
		intensity = intensity * 0.02;
	}
	else if (intensity > 0.3) {
		intensity = intensity * 0.02;
	}
	else if (intensity > 0.2) {
		intensity = intensity * 0.01;
	}
	else if (intensity > 0.08) {
		intensity = intensity * 0.005;
	}
	else {
		intensity = intensity * 0.0001;
	}
	*/

	normal		= gl_NormalMatrix * gl_Normal;
	gl_Position	= ftransform();
}