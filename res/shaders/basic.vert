#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTextureIndex;

out vec2 TexCoord;
flat out float TextureIndex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	TexCoord = aTexCoord;
	TextureIndex = aTextureIndex;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}