#pragma once

#include <string>

class EventData {
public:
	virtual ~EventData() {}
	std::string getEventName() {
		return std::string(typeid(*this).name());
	}
};