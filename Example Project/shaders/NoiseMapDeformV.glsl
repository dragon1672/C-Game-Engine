#version 400

in layout(location=0) vec3 pos;
in layout(location=2) vec3 norm;
in layout(location=3) vec2 uv;

out vec2 outUv;

uniform vec2 uvOffset;
uniform sampler2D noiseMap;
uniform float magnitude;

//mats
uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;

void main() {
	vec3 pos = pos; // copy so I can edit and replace name
	float offset = magnitude * texture(noiseMap,uvOffset+uv)[1];
	pos += offset * norm;
	vec4 transformedPos =  model2WorldTransform * vec4(pos.x,pos.y,pos.z,1);
	gl_Position =  viewTransform * transformedPos;
	outUv = uv;
}