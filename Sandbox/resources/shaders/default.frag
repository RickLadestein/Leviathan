#version 330 core
uniform vec3 cam;

out vec4 FragColor;
in vec3 TexCoord;
in vec3 Normal;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	vec4 color = texture(texture0, vec2(TexCoord[0], TexCoord[1]));
	vec4 color2 = texture(texture1, vec2(TexCoord[0], TexCoord[1]));
	float alpha = color.w;
	float likeness = clamp(dot(Normal, vec3(0.0, 1.0, 0.0)), 0.2, 1.0);
	
	if(color2.w == 0.0f) {
		color = color * likeness;
	} else {
		color = color2 * likeness;
	}
	
	
	color.w = alpha;
	FragColor = color;
} 