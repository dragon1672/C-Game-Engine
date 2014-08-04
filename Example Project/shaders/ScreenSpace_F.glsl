#version 400

in vec2 outUv;
out vec4 finalColor;

uniform float power;
uniform sampler2D myTexture;

void main() {
	finalColor = texture(myTexture,outUv);
	finalColor[0] = pow(finalColor[0],power);
	finalColor[1] = pow(finalColor[1],power);
	finalColor[2] = pow(finalColor[2],power);
	finalColor.a = 1;
}