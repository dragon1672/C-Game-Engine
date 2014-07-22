#version 400

in layout(location=0) vec3 pos;
in layout(location=3) vec2 uv;

out vec2 outUv;
out vec4 outCol;
out vec3 outPos;

//mats
uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;

void main() {
	vec4 transformedPos =  model2WorldTransform * vec4(pos.x,pos.y,pos.z,1);
	gl_Position =  viewTransform * transformedPos;
	outPos = vec3(transformedPos);
	outUv = uv;
	outCol = vec4(1,1,1,1);
}