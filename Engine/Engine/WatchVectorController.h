#pragma once

#include <Qt/qlabel.h>
#include <sstream>
#include <glm/glm.hpp>
#include "ExportHeader.h"

namespace DebugMenuControllers {
	struct ENGINE_SHARED WatchVectorController {
		const char * title;
		QLabel * label;
		glm::vec3 * data;

		WatchVectorController() {
			label = new QLabel() ;
		}

		inline void init(const char * name, glm::vec3 * toWatch) {
			title = name;
			data = toWatch;
			label->setText(name);
			update();
		}
		inline void update() {
			std::stringstream ss;
			ss << std::fixed << std::setprecision( 6 ) << title << ": {" << data->x << ", " << data->y << ", " << data->z << " }";
			label->setText(QString( ss.str().c_str() ));
		}
	};
}