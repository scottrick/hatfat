uniform vec3 BrickColor;
uniform vec3 MortarColor;

uniform vec2 BrickSize;
uniform vec2 BrickPercent;

varying vec2 vMCPosition;
varying float lightIntensity;

void main() 
{
	vec3 vColor;
	vec2 vPosition;
	vec2 vUseBrick;

	vPosition = vMCPosition / BrickSize;

	if (fract(vPosition.y * 0.5) > 0.5)
	{
		vPosition.x += 0.5;
	}

	vPosition = fract(vPosition);

	vUseBrick = step(vPosition, BrickPercent);

	vColor = mix(MortarColor, BrickColor, vUseBrick.x * vUseBrick.y);
	vColor *= lightIntensity;

	gl_FragColor = vec4(vColor, 1.0);
}