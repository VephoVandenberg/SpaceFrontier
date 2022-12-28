#version 330 core
layout (location = 0) in vec3 inPos;

out vec4 fragColor;

void main()
{
	gl_Position = vec4(inPos, 1.0f);
	fragColor = gl_Position;
}