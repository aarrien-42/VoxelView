#version 410 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 fragColor;

uniform sampler2D ourTexture;

void main()
{
	fragColor = texture(ourTexture, TexCoord);
}