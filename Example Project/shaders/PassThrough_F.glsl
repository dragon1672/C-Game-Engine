#version 400

//PassThrough FragShader

in vec2 outUv;

uniform sampler2D myTexture;

void main() {
	gl_FragColor = texture(myTexture, outUv) + vec4(0,0,0,1);
}