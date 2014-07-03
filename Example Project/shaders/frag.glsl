#version 400

//PassThrough FragShader

in vec4 outCol;

uniform vec3 blendColor;

void main() {
	gl_FragColor = outCol * vec4(blendColor,1);
}