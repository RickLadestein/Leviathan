#version 330 core
out vec4 FragColor;

in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec3 TexCoord;
in float visibility;

uniform sampler2D ourTexture;
void main()
{
	vec4 color = texture(ourTexture, vec2(TexCoord[0], TexCoord[1]));
	vec4 fogColor = vec4(0.25, 0.25, 0.25, 1.0);
	color = color * vertexColor;
	vec4 finalcolor = mix(color, fogColor, visibility);
	FragColor = finalcolor;
} 