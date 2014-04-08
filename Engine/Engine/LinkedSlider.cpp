#include "LinkedSlider.h"

void LinkedSlider::valueChanged(float newValue) {
	DebugSlider::valueChanged(newValue);
	*boundValue = newValue;
}