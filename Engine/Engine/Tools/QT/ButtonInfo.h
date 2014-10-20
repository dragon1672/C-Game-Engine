#pragma once

#include <QtWidgets/qpushbutton.h>
#include <Engine\FastDelegate.h>

class ButtonInfo : public QObject {
public:
	QPushButton* button;
	fastdelegate::FastDelegate0<> myDelegate;
	void init(const char * text, fastdelegate::FastDelegate0<> myDelegate) {
		button = new QPushButton(text);
		this->myDelegate = myDelegate;
		connect( button, &QPushButton::clicked, [this](){this->myDelegate();});
	}
};