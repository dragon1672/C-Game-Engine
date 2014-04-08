#pragma once

#include <Qt/qlabel.h>
#include "LinkedSlider.h"
#include "ExportHeader.h"

namespace DebugMenuControllers {
	struct ENGINE_SHARED SlideFloatController {
		QLabel * label;
		float * data;
		LinkedSlider * slider;
		SlideFloatController() {
			label = new QLabel();
			slider = new LinkedSlider();
		}
		inline void init(const char * name, float * toWatch, float min, float max) {
			data = toWatch;
			label->setText(name);
			slider->setMin(min);
			slider->setMax(max);
			updateModeltoGUI();
		}
		inline void updateGUItoModel() {
			// not required
		}
		inline void updateModeltoGUI() {
			slider->setBoundValue(data);
		}
	};
}