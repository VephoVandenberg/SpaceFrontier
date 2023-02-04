#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoords;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

out vec2 fragTexCoords;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(inPos, 1.0f);
	fragTexCoords = inTexCoords;
}