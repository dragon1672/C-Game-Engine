#pragma once

#include <Qt/qpushbutton.h>

typedef void BASIC_CALLBACK();

class ButtonInfo : public QObject {
	Q_OBJECT
public:
	QPushButton* button;
	BASIC_CALLBACK myDelegate;
	void init(const char * text, BASIC_CALLBACK myDelegate) {
		button = new QPushButton(text);
		this->myDelegate = myDelegate;
		QObject::connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked())); 
	}
private slots:
	void buttonClicked() {
		myDelegate();
	}
};