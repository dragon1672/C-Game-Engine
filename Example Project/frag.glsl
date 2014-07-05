#version 400

//PassThrough FragShader

in vec4 outCol;
in vec2 outUV;

uniform sampler2D myTexture;

void main() {
	gl_FragColor = texture(myTexture,outUV);
}