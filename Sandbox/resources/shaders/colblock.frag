#version 330 core

uniform sampler2D texture_0;
uniform sampler2D texture_1;
uniform float time;

out vec4 FragColor;
in vec3 TexCoord;
in vec3 Normal;

float convertrange(float value, float old_max, float new_max) {
    float percentage = (value / old_max) * 100.0;
    return (new_max / 100.0) * percentage;
}

void main()
{
    vec2 cell_center = vec2(0.5,0.5);
    float segments = 20.0;
    
    float x_pos = (mod(TexCoord.x, (1.0/ segments)));
    float y_pos = (mod(TexCoord.y, (1.0/ segments)));
    x_pos = convertrange(x_pos, (1.0/segments), 1.);
    y_pos = convertrange(y_pos, (1.0/segments), 1.);
    float dst = 1. - distance(vec2(x_pos, y_pos), cell_center);
    dst = max(dst - 0.5, 0.0);
	vec4 color = vec4(dst,dst, dst,1.0);
	color = mix(color, texture2D(texture_0, TexCoord.xy), sin(time));
	color = mix(color, texture2D(texture_1, TexCoord.xy), sin(time));
	FragColor = color;
} 