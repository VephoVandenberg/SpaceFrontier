#version 330 core

in vec2 fragTexCoords;

uniform vec3 u_Color;

void main()
{
	gl_FragColor = vec4(u_Color, 1.0f);
}