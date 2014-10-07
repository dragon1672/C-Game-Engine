#pragma once

#include <Engine/Tools/Timer.h>
#include <ExportHeader.h>
#include <Engine/Defines/SingletonsDefine.h>

#define Time TimeSingle::getInstance()

class ENGINE_SHARED TimeSingle {
	DEFINE_SINGLETON(TimeSingle)
	Timer _timer;
public:
	bool startup();
	bool shutdown();
	void update();
	float deltaTime();
	float runningTime();
};