#version 400

in vec2 outUv;
out vec4 finalColor;
//mats
uniform sampler2D myTexture;
uniform float layer;
uniform vec3 baseColor;

void main() {
	int index = int(layer-1);
	float finalValue = texture(myTexture,outUv)[index];
	finalColor = vec4(finalValue,finalValue,finalValue,1);
	finalColor *= vec4(baseColor,1);
	//finalColor = vec4(1,1,1,1);
}