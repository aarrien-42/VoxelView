#version 440 core

in vec2 TexCoord;
flat in int TextureIndex;

out vec4 FragColor;

uniform sampler2DArray textureArray;

void main()
{
    FragColor = texture(textureArray, vec3(TexCoord, 0));
}