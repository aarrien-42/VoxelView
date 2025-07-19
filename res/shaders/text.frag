#version 440 core

in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 textColor;
uniform sampler2D textTexture;

void main () {
	vec4 textureColor = texture(textTexture, TexCoord);
	FragColor = vec4 (textColor, textureColor.r);
}
