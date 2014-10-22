#pragma once

#include <ExportHeader.h>

namespace DefaultShaders {
	namespace VertexShader {
		//inline to display code for easy understanding
		ENGINE_SHARED inline const char * DefaultVertShader() {
			//return ""
			//	"#vert_shaderstart       \n"
			//	"                        \n"
			//	"void main() {           \n"
			//	"   #vert_main_export    \n"
			//	//"   #vert_main_setglpos  \n"
			//	" fragCol = vec4(tangent);\n"
			//	//" gl_Position = vec4(1,1,1,1);                       \n"
			//	" gl_Position = vec4(pos,1);                       \n"
			//	"}                       \n"
			//	"";
			return "#version 400\n"
				"in layout(location=0) vec3 pos;							  \n"
				"in layout(location=1) vec4 col;							  \n"
				"in layout(location=2) vec3 two;							  \n"
				"in layout(location=3) vec3 thr;							  \n"
				"															  \n"
				"out vec4 fragCol;											  \n"
				"out vec3 fragPos;											  \n"
				"out vec3 fragWorldPos;										  \n"
				"															  \n"
				"//mats														  \n"
				"uniform mat4x4 perspective;								  \n"
				"uniform mat4x4 model2WorldTransform;						  \n"
				"uniform mat4x4 MVP;                 						  \n"
				"															  \n"
				"void main() {												  \n"
				"	vec4 transformedPos = model2WorldTransform * vec4(pos,1); \n"
				//"	gl_Position = vec4(pos.xyz,1);	    		  \n"
				"	gl_Position = MVP*vec4(pos,1);	    		  \n"
				"	fragCol = col;											  \n"
				"	fragPos = pos;											  \n"
				"	fragWorldPos = vec3(transformedPos);					  \n"
				"}															  \n"
				"															  \n";
		}
	}
	namespace FragShader {
		ENGINE_SHARED inline const char * FragModelColor() {
			//return ""
			//	"#frag_start                        \n"
			//	"#frag_import                       \n"
			//	"                                   \n"
			//	"void main() {                      \n"
			//	"   gl_FragColor = fragCol; \n"
			//	//"   gl_FragColor = vec4(1,1,1,1); \n"
			//	"}                                  \n"
			//	"";
			return "#version 400\n"
				"												\n"
				"in vec4 fragCol;											  \n"
				"in vec3 fragPos;											  \n"
				"in vec3 fragWorldPos;										  \n"
				"												\n"
				"void main() {									\n"
				"	gl_FragColor = fragCol;				\n"
				"}												\n"
				"";
		}
	}
}