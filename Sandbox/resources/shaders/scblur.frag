#version 330 core
out vec4 FragColor;
in vec3 TexCoord;
in vec3 Normal;

uniform sampler2D texture_0;
uniform float time;

void main()
{
	vec4 color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	float sample_offset = 0.01;

	vec2 offsets[9] = vec2[9](
  		vec2(TexCoord.x - sample_offset, TexCoord.y - sample_offset ), 	vec2(TexCoord.x, TexCoord.y - sample_offset ), 	vec2(TexCoord.x + sample_offset, TexCoord.y - sample_offset ),
  		vec2(TexCoord.x - sample_offset, TexCoord.y), 					vec2(TexCoord.x, TexCoord.y), 					vec2(TexCoord.x + sample_offset, TexCoord.y),
  		vec2(TexCoord.x - sample_offset, TexCoord.y + sample_offset ), 	vec2(TexCoord.x, TexCoord.y + sample_offset ), 	vec2(TexCoord.x + sample_offset, TexCoord.y + sample_offset )
	);

	float mask[9] = float[9] (
		0.0, -2.0, 0.0,
		-2.0, 4.0, -2.0,
		0.0, -2.0, 0.0
	);

	float devision_factor = 0.0f;
	for(int i = 0; i < 9; i++) {
		color += texture(texture_0, -offsets[i].yx) * mask[i];
		devision_factor += mask[i];
	}

	color = color / devision_factor;

	//vec4 color = texture(texture_0, -TexCoord.yx);
	FragColor = color;
} 