#version 400

in layout(location=0) vec3 pos;
in layout(location=3) vec2 uv;

out vec2 outUv;

//mats
uniform mat4x4 meTransform;

void main() {
	gl_Position =  meTransform * vec4(pos,1);
	outUv = uv;
}