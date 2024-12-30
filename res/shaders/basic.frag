#version 440 core

in vec2 TexCoord;
flat in float TextureIndex;

out vec4 FragColor;

uniform sampler2DArray textureArray;

void main()
{
    FragColor = texture(textureArray, vec3(TexCoord, TextureIndex));
}