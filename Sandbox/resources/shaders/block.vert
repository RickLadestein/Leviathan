#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aTex;
layout (location = 3) in vec4 iPos;

out vec4 vertexColor; // specify a color output to the fragment shader
out vec3 TexCoord;
out float visibility;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cam;

const float density = 0.03;
const float gradient = 10;
const float fog_dist = 16.0;

vec3 GetTextureCoords(vec3 input, float id)
{
	//return coords;
	vec3 output = input;
	if(aNorm[1] == -1) {
		if(id == 5) {
			id = 4;
		}
		
		if(id == 8) {
			id = 255;
		}
	}
	
	if(aNorm[1] == 1) {
		if(id == 5) {
			id = 256;
		}
		
		if(id == 8) {
			id = 255;
		}
	}
	
	float r_id = id - 1;
	float x = floor(mod(r_id, 16.0f));
	float y = floor(r_id / 16.0f);
	output[0] = output.x + (x * 0.0625f);
	output[1] = output.y - (y * 0.0625f);
	output.z = r_id;
	return output;
}

void main()
{
	vec4 realpos_in_chunk = vec4((aPos + vec3(iPos.x, iPos.y, iPos.z)), 1.0);
	vec4 realpos = model * realpos_in_chunk;
	vec3 distanceToCam = realpos.xyz - cam;
	float distance = length(distanceToCam) - fog_dist;
	if(distance < 0) {
		distance = 1;
	}
	visibility = exp(-pow((distance*density),gradient));
	visibility = clamp(visibility, 0.0, 1.0);
	visibility = 1.0f - visibility;
	
	vertexColor = vec4(1.0, 1.0, 1.0, 1.0);
    gl_Position = projection * view * model * realpos_in_chunk;
	if(aNorm[1] == 1) {
		if(iPos[3] == 5) {
			vertexColor = vec4(0.35, 1.0, 0.35, 1.0);
		}
	} else if(aNorm[0] == 1 || aNorm[0] == -1 || aNorm[2] == 1 || aNorm[2] == -1) {
		vertexColor = vec4(0.8, 0.8, 0.8, 1.0);
	} else {
		vertexColor = vec4(0.5, 0.5, 0.5, 1.0);
	}
	TexCoord = GetTextureCoords(aTex, iPos[3]);
}