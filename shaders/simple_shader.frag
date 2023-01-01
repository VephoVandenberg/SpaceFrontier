#version 330 core

in vec2 fragTexCoords;

uniform sampler2D uTexture;

void main()
{
	gl_FragColor = texture(uTexture, fragTexCoords) * vec4(0.3f, 0.2, 0.0f, 1.0f);
}