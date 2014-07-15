#version 400

in vec2 outUv;
out vec4 finalColor;
//mats
uniform sampler2D myTexture;

void main() {
	finalColor = texture(myTexture,outUv);
}