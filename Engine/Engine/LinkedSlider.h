#pragma once

#include "DebugSlider.h"
#include "ExportHeader.h"

class ENGINE_SHARED LinkedSlider : public DebugSlider {
	float * boundValue;

	//override
	void valueChanged(float newValue);
public:

	
	LinkedSlider(
		float * boundFloat=nullptr,
		float min = 0.0f, float max = 1.0f, 
		bool textOnLeft = false,
		float granularity = 40.0)
			: DebugSlider(min, max,textOnLeft,granularity)
	{
			boundValue = boundFloat;
	}
	inline void setBoundValue(float * toSet) {
		boundValue = toSet;
		setValue(*boundValue);
	}
};