#version 330 core
out vec4 FragColor;
in vec3 TexCoord;
in vec3 Normal;

void main()
{
	vec4 color = vec4(0.25, 0.75, 0.25, 1.0);
	FragColor = color;
} 