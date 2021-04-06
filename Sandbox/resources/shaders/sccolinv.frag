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
	vec4 color = texture(texture_0, -TexCoord.yx);
	vec4 corrcolor = vec4(1.0, 1.0, 1.0, 1.0) - color;
	corrcolor.w = 1.0f;
	FragColor = corrcolor;
} 