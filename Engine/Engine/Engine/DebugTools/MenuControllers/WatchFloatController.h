#pragma once

#include <sstream>
#include <Qt/qlabel.h>
#include <Qt/qstring.h>
#include <ExportHeader.h>
#include <iomanip>

namespace DebugMenuControllers {
	struct ENGINE_SHARED WatchFloatController {
		const char * title;
		float * data;
		QLabel * label;
		WatchFloatController() {
			label = new QLabel();
		}
		inline void init(const char * name, float * toWatch) {
			title = name;
			data = toWatch;
			update();
		}
		inline void update() {
			std::stringstream ss;
			ss << title << ": " << std::fixed << std::setprecision( 6 ) << *data;
			label->setText(QString( ss.str().c_str() ));
		}
	};
}