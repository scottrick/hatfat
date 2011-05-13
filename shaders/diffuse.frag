varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec3 hVector;

const vec4 AmbientColor = vec4(0.15, 0.15, 0.15, 1.0);
const vec4 DiffuseColor = vec4(1.0, 1.0, 1.0, 1.0);

void main()
{
	vec3 normalized_normal = normalize(normal);
	vec3 normalized_vertex_to_light = normalize(vertex_to_light_vector);
	vec3 normalize_hVector = normalize(hVector);

	float diffuseTerm = clamp(dot(normal, normalized_vertex_to_light), 0.0, 1.0);
	
	gl_FragColor = AmbientColor + diffuseTerm * DiffuseColor;
}
