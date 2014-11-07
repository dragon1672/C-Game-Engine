#pragma once

#include <QtWidgets/qpushbutton.h>
#include <Engine\FastDelegate.h>
#include <functional>

class ButtonInfo : public QObject {
public:
	QPushButton* button;
	void init(const char * text, fastdelegate::FastDelegate0<> myDelegate) {
		button = new QPushButton(text);
		connect( button, &QPushButton::clicked, [=](){myDelegate();});
	}
	void init(const char * text, std::function<void()> myDelegate) {
		button = new QPushButton(text);
		connect( button, &QPushButton::clicked, [=](){myDelegate();});
	}
};