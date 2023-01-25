#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoords;

uniform mat4 uProjView;
uniform mat4 uModel;

void main()
{
	gl_Position = uProjView * uModel * vec4(inPos, 1.0f);
}