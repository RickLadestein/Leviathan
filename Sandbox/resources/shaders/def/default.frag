#version 330 core
uniform vec3 cam;

out vec4 FragColor;
in vec3 TexCoord;
in vec3 Normal;

void main()
{
	vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
	FragColor = color;
} 