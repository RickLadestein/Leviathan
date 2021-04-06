#version 330 core
out vec4 FragColor;
in vec3 TexCoord;
in vec3 Normal;


uniform vec3 light = vec3(0.0f, 5.0f, 0.0f);


void main()
{
	float intensity = dot(light, Normal);
	vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	if (intensity > 0.98)
		color = vec4(1.0,0.5,0.5,1.0);
	else if (intensity > 0.5)
		color = vec4(0.6,0.3,0.3,1.0);
	else if (intensity > 0.25)
		color = vec4(0.4,0.2,0.2,1.0);
	else
		color = vec4(0.2,0.1,0.1,1.0);
	FragColor = color;
} 