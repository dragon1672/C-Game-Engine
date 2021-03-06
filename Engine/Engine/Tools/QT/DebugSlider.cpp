#include <Engine\Tools\QT\DebugSlider.h>
#include <QtWidgets\qvboxlayout>
#include <QtWidgets\qslider>
#include <QtWidgets\qlabel>

DebugSlider::DebugSlider(float min, float max, bool textOnLeft, float granularity) {
	QLayout* layout;
	this->min = min;
	this->max = max;
	sliderGranularity = granularity;
	setLayout(layout = textOnLeft ? (QLayout*)new QHBoxLayout : new QVBoxLayout);
	layout->addWidget(label = new QLabel);
	label->setMinimumWidth(35);
	layout->addWidget(slider = new QSlider);
	label->setAlignment(Qt::AlignCenter);
	slider->setOrientation(Qt::Horizontal);
	slider->setMinimum(0);
	slider->setMaximum(sliderGranularity);

	connect( slider, &QSlider::valueChanged, [this](){this->sliderValueChanged();});

	sliderValueChanged();
}

float DebugSlider::value() const {
	//int slideVal = slider->value();
	return min + (max - min) * (slider->value() / sliderGranularity);
}

void DebugSlider::setValue(float newValue) {
	float spot = (newValue - min) / (max - min);
	slider->setValue(spot * sliderGranularity);
}

void DebugSlider::sliderValueChanged() {
	label->setText(QString::number(value()));
	emit valueChanged(value());
}
void DebugSlider::setMin(float newMin) {
	float val = value();
	min = newMin;
	val = val < min ? min : val; // clip if needed
	setValue(val);
}
void DebugSlider::setMax(float newMax) {
	float val = value();
	max = newMax;
	val = val > max ? max : val; // clip if needed
	setValue(val);
}
void DebugSlider::setGranularity(float newGranularity) {
	float val = this->value();
	sliderGranularity = newGranularity;
	slider->setMaximum(sliderGranularity);
	setValue(val);
}