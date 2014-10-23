#pragma once

#include <ExportHeader.h>

namespace DefaultShaders {
	namespace VertexShader {
		//inline to display code for easy understanding
		ENGINE_SHARED inline const char * DefaultVertShader() {
			return ""
				"#vert_shaderstart       \n"
				"                        \n"
				"void main() {           \n"
				"   #vert_main_export    \n"
				"   #vert_main_setglpos  \n"
				"}                       \n"
				"";
		}
	}
	namespace FragShader {
		ENGINE_SHARED inline const char * FragModelColor() {
			return ""
				"#frag_start                        \n"
				"#frag_import                       \n"
				"                                   \n"
				"void main() {                      \n"
				"   gl_FragColor = fragCol; \n"
				"}                                  \n"
				"";
		}
	}
}