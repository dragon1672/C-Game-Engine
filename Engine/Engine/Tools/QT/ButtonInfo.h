#pragma once

#include <Qt/qpushbutton.h>
#include <Engine\FastDelegate.h>

class ButtonInfo : public QObject {
	Q_OBJECT
public:
	QPushButton* button;
	fastdelegate::FastDelegate0<> myDelegate;
	void init(const char * text, fastdelegate::FastDelegate0<> myDelegate) {
		button = new QPushButton(text);
		this->myDelegate = myDelegate;
		QObject::connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked())); 
	}
private slots:
	void buttonClicked() {
		myDelegate();
	}
};