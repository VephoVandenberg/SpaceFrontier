#version 330 core

in vec2 fragTexCoords;

uniform sampler2D uTexture;

void main()
{
	gl_FragColor = texture(uTexture, fragTexCoords);
}