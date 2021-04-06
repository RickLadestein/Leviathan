#version 330 core

uniform sampler2D texture_0;
uniform sampler2D texture_1;
uniform float time;

out vec4 FragColor;
in vec3 TexCoord;
in vec3 Normal;

void main()
{
	vec4 color1 = texture2D(texture_0, TexCoord.xy);
    vec4 color2 = texture2D(texture_1, TexCoord.xy);
    float side = (sin(time) + 1.0f) / 2.0f;
    vec4 color = mix(color1, color2, side);
	FragColor = color;
} 