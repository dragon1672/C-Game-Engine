#pragma once
#ifndef AUTO_PROFILE_H
#define AUTO_PROFILE_H

#include "Timer.h"
#include "AutoProfileManager.h"
#include "ExportHeader.h"

class ENGINE_SHARED AutoProfile {
private:
	const char* profileName;
	Timer myTimer;
public:
	AutoProfile(const char* name) {
		profileName = name;
		myTimer.start();
	}
	~AutoProfile() {
		float temp = myTimer.stop() * 1000;//converting to miliseconds
		AutoProfileManager::addEntry(profileName,temp);
	}
};

#endif