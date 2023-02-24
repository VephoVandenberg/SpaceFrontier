#version 330 core

out vec4 oColor;

in vec2 fragTexCoords;

uniform sampler2D uTexture;
uniform vec3 u_Color;

void main()
{
	oColor = vec4(u_Color, 1.0f) * texture(uTexture, fragTexCoords);
}
