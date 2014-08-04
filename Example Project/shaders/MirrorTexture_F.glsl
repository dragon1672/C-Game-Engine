#version 400

//PassThrough FragShader

in vec2 fragUv;

out vec4 finalColorForOutput;

uniform sampler2D myTexture;

void main() {
	finalColorForOutput = texture(myTexture,fragUv) * vec4(.9,1,.9,1);
}