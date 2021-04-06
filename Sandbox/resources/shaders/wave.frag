#version 330 core
out vec4 FragColor;
in vec3 TexCoord;
in vec3 Normal;
in vec3 Pos;

uniform float time;
uniform sampler2D texture_0;

float amplitude = 0.1f;
float y_offset = 0.5f;
float x_offset = 0.0f;
float frequency = 2.5f;

void main()
{
	 x_offset = Pos.x;
	float textureoffset = amplitude + amplitude * sin((time * frequency) + (x_offset * frequency));
	vec4 color = texture(texture_0, vec2(TexCoord.x, TexCoord.y + textureoffset));
	FragColor = color;
} 