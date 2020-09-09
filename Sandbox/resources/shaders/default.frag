#version 330 core
uniform vec3 cam;

out vec4 FragColor;
in vec3 TexCoord;
in vec3 Normal;

uniform sampler2D ourTexture;
void main()
{
	vec4 color = vec4(1.0);
	float alpha = color.w;
	float likeness = clamp(dot(Normal, vec3(0.0, 1.0, 0.0)), 0.2, 1.0);
	
	color = color * likeness;
	
	color.w = alpha;
	FragColor = color;
} 