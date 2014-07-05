#version 400

in layout(location=0) vec3 pos;
in layout(location=1) vec3 col;
in layout(location=3) vec2 uv;

out vec3 outCol;
out vec2 outUV;

//mats
uniform mat4x4 viewTransform;
uniform mat4x4 whereMat;

void main() {
	vec4 transformedPos =  whereMat * vec4(pos.x,pos.y,pos.z,1);
	gl_Position =  viewTransform * transformedPos;
	outCol = col;
	outUV = uv;
}