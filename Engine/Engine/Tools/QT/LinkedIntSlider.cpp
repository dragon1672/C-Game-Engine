#include <Engine\Tools\QT\LinkedIntSlider.h>

void LinkedIntSlider::valueChanged(float newValue) {
	DebugSlider::valueChanged(newValue);
	*boundValue = (int)newValue;
}