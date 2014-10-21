#pragma once

#include <ExportHeader.h>

namespace DefaultShaders {
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