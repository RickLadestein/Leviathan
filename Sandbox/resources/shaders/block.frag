#version 330 core

out vec4 FragColor;
in vec3 TexCoord;
in vec3 Normal;

void main()
{
	vec4 color = vec4(vec3(abs(Normal.x), abs(Normal.y), abs(Normal.z)), 1.0);
	FragColor = color;
} 