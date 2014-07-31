#version 400

in layout(location=0) vec3 pos;

out vec3 fragPos;

//mats

uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;

void main() {
	vec4 transformedPos =  model2WorldTransform * vec4(pos,1);
	gl_Position =  viewTransform * transformedPos;
	fragPos = vec3(pos);
}