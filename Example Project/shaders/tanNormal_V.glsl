#version 400

in layout(location=0) vec3 pos;
in layout(location=1) vec3 tan;
in layout(location=2) vec3 norm;
in layout(location=3) vec2 uv;

out vec2 outUv;
out vec3 outTan;
out vec3 outPos;
out vec3 outNorm;
out mat3 texture2ModelTransform;

out vec3 outCol;

//mats
uniform mat4x4 viewTransform;
uniform mat4x4 model2WorldTransform;

void main() {
	vec4 transformedPos =  model2WorldTransform * vec4(pos.x,pos.y,pos.z,1);
	gl_Position =  viewTransform * transformedPos;
	vec3 biTan = cross(norm,tan);
	
	outCol = vec3(uv,1);
	
	texture2ModelTransform = mat3(tan, biTan,norm);
	outPos = vec3(transformedPos);
	outUv = uv;
	outTan = vec3(tan);
	outNorm = norm;
}