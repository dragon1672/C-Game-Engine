#ifndef DEBUG_SLIDER_H
#define DEBUG_SLIDER_H
#include <QtGui\qwidget>
#include "ExportHeader.h"
class QSlider;
class QLabel;

class ENGINE_SHARED DebugSlider : public QWidget {
	
	Q_OBJECT

	QSlider* slider;
	QLabel* label;
	float sliderGranularity;
	float min;
	float max;

private slots:
	void sliderValueChanged();

signals:
	virtual void valueChanged(float newValue);

public:
	DebugSlider(
	float min = -10.0f, float max = 10.0f, 
	bool textOnLeft = false, float granularity = 100.0);
	float value() const;
	void setValue(float newValue);
	void setMin(float newMin);
	void setMax(float newMax);
};

#endif