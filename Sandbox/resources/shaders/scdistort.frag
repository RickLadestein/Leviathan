#version 330 core
out vec4 FragColor;
in vec3 TexCoord;
in vec3 Normal;

uniform sampler2D texture_0;
uniform float time;

float amplitude = 0.1f;
float y_offset = 0.5f;
float x_offset = 0.0f;
float frequency = 2.5f;

void main()
{
	 x_offset = TexCoord.x;
	float textureoffset = amplitude + amplitude * sin((time * frequency) + (x_offset * frequency));
	vec4 color = texture(texture_0, -vec2(TexCoord.y + textureoffset, TexCoord.x));
	FragColor = color;
} 