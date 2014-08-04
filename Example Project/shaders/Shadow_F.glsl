#version 400

//PassThrough FragShader

in vec2 fragUv;
in vec3 fragCol;
in vec3 fragNorm;
in vec3 fragPos;
in vec4 ShadowCoord;

out vec4 finalColorForOutput;

uniform vec3  lightColor;
uniform vec3  diffusePos;
uniform float specPower;
uniform vec3  camPos;

uniform sampler2D shadowMap;
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

uniform float thres;

void main() {
	float visibility = 0;
	//check depth
	float shadowIntensity = textureProj( shadowMap, ShadowCoord );
	
	if(abs(shadowIntensity - ShadowCoord.z/ShadowCoord.w) < thres) {
		visibility = 1;
		//finalColorForOutput = texture(shadowMap, ShadowCoord.xy);
		//finalColorForOutput.r = pow(finalColorForOutput.r,100);
		//finalColorForOutput.g = pow(finalColorForOutput.g,100);
		//finalColorForOutput.b = pow(finalColorForOutput.b,100);
		//finalColorForOutput = vec4(ShadowCoord.xy,1,1);
		//finalColorForOutput.a = 1;
		//return;
	}
	//lighting
	vec3 finalCol = vec3(1,1,1);
	vec3 lightV;
	calculateVectors(vec3(fragPos));
	lightV = diffuseLightAmount();
	finalCol = visibility * finalCol * lightV + specLight();
	finalColorForOutput = vec4(finalCol,1);
	
	
	
	
	
	//finalColorForOutput.r = pow(shadowIntensity,56);
	//finalColorForOutput.g = pow(shadowIntensity,56);
	//finalColorForOutput.b = pow(shadowIntensity,56);
	//finalColorForOutput.a = 1;
	
	//finalColorForOutput = vec4(lightV,1);
	//finalColorForOutput = vec4(rotatedNormal,1);
	//finalColorForOutput = vec4(outCol,1);
}