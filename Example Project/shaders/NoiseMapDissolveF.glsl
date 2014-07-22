#version 400

in vec2 outUv;
out vec4 finalColor;
//mats
uniform sampler2D myTexture;
uniform sampler2D noiseMap;
uniform float discardThreshold;

void main() {
	if(texture(noiseMap,outUv).r < discardThreshold) discard;
	finalColor = texture(myTexture,outUv);
	//finalColor = texture(noiseMap,outUv);
	float noise = texture(noiseMap,outUv).r - discardThreshold;
	if(noise < .01) {
		vec3 fireStart = vec3(0,0,.8);
		vec3 fireEnd = vec3(1,1,0);
		float percent = noise / .01;
		finalColor = vec4((1-percent) * fireEnd + (percent * fireStart),1);
	}
	finalColor.a = 1;
	//finalColor = vec4(discardThreshold*vec3(1,1,1),1);
}