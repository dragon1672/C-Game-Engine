#version 400

//PassThrough FragShader

in vec2 outUv;
in vec4 outCol;

uniform sampler2D myTexture;
uniform sampler2D myAlpha;

void main() {
	vec4 alpha = texture(myAlpha,outUv);
	if(alpha == vec4(0,0,0,1)) discard;
	gl_FragColor = texture(myTexture, outUv);
	//gl_FragColor = vec4(1,1,1,1);
}