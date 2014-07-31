#version 400

//PassThrough FragShader

in vec2 fragUv;
in vec3 fragCol;
in vec3 fragNorm;
in vec3 fragPos;

out vec4 finalColorForOutput;

uniform vec3  lightColor;
uniform vec3  diffusePos;
uniform float specPower;
uniform vec3  camPos;

uniform samplerCube cubeMap;
uniform mat4 modelRotation;

vec3 rotatedNormal; // the 'real' normal
vec3 diffuseVector; // vector between point and light
vec3 eyeVector;     // vector between point and camera
vec3 specVector;    // vector of Spec Reflection (aka diffuse reflection)


void calculateVectors(vec3 vertPos) {
	rotatedNormal = mat3(modelRotation) * fragNorm;
	diffuseVector = normalize(diffusePos - vertPos);
	eyeVector = normalize(camPos - vertPos);
	specVector = -reflect(diffuseVector,rotatedNormal);
}
vec3 diffuseLightAmount() {
	return dot(rotatedNormal,diffuseVector) * lightColor;
}
vec3 specLight() {
	float cosAngle = clamp(dot(eyeVector,specVector),0,1);
	float specCoeff = pow(cosAngle,specPower);
	return specCoeff * lightColor;
}

vec3 combineLight(vec3 one, vec3 two) {
	//return one + two;
	float x = max(one.x , two.x);
	float y = max(one.y , two.y);
	float z = max(one.z , two.z);
	return vec3(x,y,z);
}

in vec3 outCol;

void main() {
	vec3 finalCol = vec3(1,1,1);
	vec3 lightV;
	calculateVectors(vec3(fragPos));
	lightV = diffuseLightAmount();
	finalCol = finalCol * lightV + specLight();
	finalColorForOutput = vec4(finalCol,1);
	//finalColorForOutput = vec4(lightV,1);
	//finalColorForOutput = vec4(rotatedNormal,1);
	//finalColorForOutput = vec4(outCol,1);
}