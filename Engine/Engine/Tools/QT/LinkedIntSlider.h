#pragma once

#include <ExportHeader.h>
#include <Engine\Tools\QT\DebugSlider.h>

class ENGINE_SHARED LinkedIntSlider : public DebugSlider {
	int * boundValue;
public:

	
	LinkedIntSlider(
		int * boundFloat=nullptr,
		float min = 0.0f, float max = 1.0f, 
		bool textOnLeft = false,
		float granularity = 100.0)
			: DebugSlider(min, max,textOnLeft,granularity)
	{
			boundValue = boundFloat;
			connect( this, &DebugSlider::valueChanged, [this](float newValue){*(this->boundValue) = (int)newValue;});
	}
	inline void setBoundValue(int * toSet) {
		boundValue = toSet;
		setValue((float)(*boundValue));
	}
};