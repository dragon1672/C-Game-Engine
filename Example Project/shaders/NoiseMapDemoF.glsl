#version 400

in vec2 outUv;
out vec4 finalColor;
//mats
uniform sampler2D myTexture;
uniform float layer;

void main() {
	int index = int(layer-1);
	float finalColor = texture(myTexture,outUv)[index];
	finalColor = vec4(finalColor,finalColor,finalColor,1);
	finalColor = vec4(1,1,1,1);
}