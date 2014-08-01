#version 400

//PassThrough FragShader

in vec3 fragNorm;
in vec3 fragPos;

out vec4 finalColorForOutput;

uniform vec3  camPos;

uniform samplerCube worldMap;
uniform mat4 modelRotation;

void main() {
	vec3 rotatedNormal = mat3(modelRotation) * fragNorm;
	vec3 eyeVector = -(camPos - fragPos);
	vec3 reflectVector = reflect(eyeVector,rotatedNormal);
	
	finalColorForOutput = texture(worldMap,reflectVector) * vec4(.9,1,.9,1);
}