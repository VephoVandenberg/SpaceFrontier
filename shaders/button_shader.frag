#version 330 core

out vec4 oColor;

uniform vec3 u_Color;

void main()
{
	oColor = vec4(u_Color, 1.0f);
}