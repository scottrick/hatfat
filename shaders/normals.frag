varying vec3 normal;
varying float intensity;

void main() 
{	
	gl_FragColor += vec4(normalize(normal) / 2.0 + 0.5, 0.2);
		
	//vec4 color = vec4(normalize(gl_FragCoord));
	//color.w = 1.0;
	//gl_FragColor = color;
}