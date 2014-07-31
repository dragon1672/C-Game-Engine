#version 400

//PassThrough FragShader

in vec3 fragPos;

out vec4 finalColorForOutput;

uniform samplerCube worldMap;

void main() {
	finalColorForOutput = texture(worldMap,fragPos);
}