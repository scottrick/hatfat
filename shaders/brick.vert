uniform vec3 LightPosition;

const float specularContribution = 0.3;
const float diffuseContribution = 1.0 - specularContribution;

varying float lightIntensity;
varying vec2 vMCPosition;

void main()
{
	vec3 vEyePosition = vec3(gl_ModelViewMatrix * gl_Vertex);

	vec3 vTransformedNormal = normalize(gl_NormalMatrix * gl_Normal);

	vec3 vLightDirection = normalize(LightPosition - vEyePosition);

	vec3 vReflectDirection = reflect(-vLightDirection, vTransformedNormal);

	vec3 vViewDirection = normalize(-vEyePosition);

	float fDiffuse = max(dot(vLightDirection, vTransformedNormal), 0.0);

	float fSpecular = 0.0;
	if (fDiffuse > 0.0)
	{
		fSpecular = max(dot(vReflectDirection, vViewDirection), 0.0);
		fSpecular = pow(fSpecular, 16.0); //higher power means a smaller, more concentrated specular highlight
	}

	lightIntensity = diffuseContribution * fDiffuse + specularContribution * fSpecular;

	vMCPosition = gl_Vertex.xy;
	//vMCPosition = ftransform();

	gl_Position = ftransform();
}