#version 400

in vec2 outUv;
out vec4 finalColor;
//mats
uniform sampler2D myTexture;
uniform vec2 uvOffset;

void main() {
	finalColor = texture(myTexture,uvOffset+outUv);
	finalColor = texture(myTexture,uvOffset+outUv).gggg;
	finalColor.a = 1;
	//finalColor = vec4(1,1,1,1);
}