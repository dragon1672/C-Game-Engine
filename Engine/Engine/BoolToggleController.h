#pragma once

#include <QtGui\qcheckbox.h>
#include "ExportHeader.h"

namespace DebugMenuControllers {
	struct ENGINE_SHARED BoolToggleController {
		QCheckBox * checkBox;
		bool * dataBound;

		BoolToggleController() {
			checkBox = new QCheckBox();
		}

		inline void init(const char * name, bool * toWatch) {
			checkBox->setText(name);
			dataBound = toWatch;
			updateModeltoGUI();
		}
		inline void updateGUItoModel() {
			*dataBound = checkBox->isChecked();
		}
		inline void updateModeltoGUI() {
			checkBox->setChecked(*dataBound);
		}
	};
}