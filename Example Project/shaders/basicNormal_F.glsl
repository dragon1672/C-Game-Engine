#version 400

in vec2 outUv;
in vec4 outCol;
in vec3 outPos;

out vec4 finalColorForOutput;


//mats
uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;
//consider sending rotation separately

//lighting data
uniform vec3  lightColor;
uniform vec3  diffusePos;
uniform float specPower;
uniform vec3  camPos;
uniform sampler2D normalMap;


uniform bool whiteAsTexture;

//repeated calculations
vec3 rotatedNormal; // the 'real' normal
vec3 diffuseVector; // vector between point and light
vec3 eyeVector;     // vector between point and camera
vec3 specVector;    // vector of Spec Reflection (aka diffuse reflection)


vec3 initTextureToNorm(vec3 input) {
	input.x = 2 * (input.x - .5);
	input.y = 2 * (input.y - .5);
	input.z = 2 * (input.z - .5);
	return input;
}
void calculateVectors(vec3 vertPos) {
	rotatedNormal = initTextureToNorm(vec3(texture(normalMap,outUv)));
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

void main() {
	vec3 finalCol = vec3(outCol);
	if(!whiteAsTexture)	finalCol = vec3(texture(normalMap,outUv));
	vec3 lightV;
	calculateVectors(vec3(outPos));
	lightV = diffuseLightAmount();
	finalCol = finalCol * lightV + specLight();
	finalColorForOutput = vec4(finalCol,1);
	//finalColorForOutput = texture(normalMap,outUv);
	//finalColorForOutput = vec4(lightV,1);
}