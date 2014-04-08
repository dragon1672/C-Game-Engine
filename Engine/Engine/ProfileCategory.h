#pragma once
#ifndef PROFILE_CATEGORY_H
#define PROFILE_CATEGORY_H

#include "ExportHeader.h"

const int MAX_FRAMES_TO_MESURE = 50;

struct ENGINE_SHARED ProfileCategory {
	ProfileCategory() {
		this->name = "";
		timesCalled = 0;
		totalTime = 0;
		min = 0;
		max = 0;
	}
	const char* name;
	int timesCalled;//also index for data
	float totalTime;
	float min;
	float max;
	float data[MAX_FRAMES_TO_MESURE];
};
#endif