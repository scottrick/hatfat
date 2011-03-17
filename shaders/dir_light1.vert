void main() 
{
	vec3 normal, lightDir;
	vec4 diffuse, ambient, globalAmbient, specular; 
	float NdotHV, NdotL; 

	/* compute diffuse! */
	normal = normalize(gl_NormalMatrix * gl_Normal);
	lightDir = normalize(vec3(gl_LightSource[0].position));
	NdotL = max(dot(normal, lightDir), 0.0);
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;

	/* compute ambient */
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;

	/* computer specular */
	if (NdotL > 0.0)
	{
		NdotHV = max(dot(normal, gl_LightSource[0].halfVector.xyz), 0.0);
		specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV, gl_FrontMaterial.shininess); 
	}
	
	gl_FrontColor = NdotL * diffuse + globalAmbient + ambient + specular;

	gl_Position = ftransform();
}
