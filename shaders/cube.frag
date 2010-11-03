varying vec3 DiffuseColor;
varying vec3 SpecularColor;
varying vec3 MCPosition;

void main()
{
	float CubeSize = 1.0;
	vec3 pos = MCPosition / CubeSize;

	pos = floor(pos);
	pos = mod(pos, 2.0);

	vec3 finalColor;
	
//	if (pos.x + pos.y + pos.z > 0.95 && pos.x + pos.y + pos.z < 1.05)
	if (pos.x + pos.y + pos.z == 1.0)
	{
		finalColor = vec3(0.6, 0.0, 0.0);
	}
	else
	{
		finalColor = vec3(0.0, 0.0, 0.0);
	}

	finalColor = finalColor * DiffuseColor + SpecularColor;

	gl_FragColor = vec4(finalColor, 1.0);
}