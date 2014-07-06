#version 400

//PassThrough FragShader

in vec2 outUv;

uniform sampler2D myTexture;
uniform vec3 blendColor;
uniform float alphaVal;

void main() {
	gl_FragColor = (vec4(blendColor,1) * texture(myTexture,outUv)) * vec4(1,1,1,alphaVal);
}