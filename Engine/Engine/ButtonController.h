#pragma once

#include  <Qt/qbuttongroup.h>
typedef void BASIC_CALLBACK();

class ButtonController {
public:
	BASIC_CALLBACK callBack;

	void init(BASIC_CALLBACK callBack) {
		this->callBack = callBack;
	}

};