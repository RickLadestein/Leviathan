#version 330 core
uniform vec3 cam;

out vec4 FragColor;
in vec3 TexCoord;
in vec3 Normal;

uniform sampler2D ourTexture;
void main()
{
	vec4 color = texture(ourTexture, vec2(TexCoord[0], TexCoord[1]));
	FragColor = color;
} 