#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <windows.h>
#include <ExportHeader.h>
#include <Engine/Defines/SingletonsDefine.h>
#include <Engine/Tools/MasterLua.h>

class ENGINE_SHARED Timer {
private:
	LARGE_INTEGER _start;
	LARGE_INTEGER _stop;
	LARGE_INTEGER _lastInterval;
	LARGE_INTEGER total;//used for pause/resume
	LARGE_INTEGER frequency;
	float LargeInt2Secs( LARGE_INTEGER & L);

	float _deltaTime;
	LUA_OBJECT(Timer);

	DEFINE_SINGLETON(Timer);
public:
	Timer();
	~Timer();
	void  start();
	float stop();
	void  pause();
	void  resume();
	float interval();
	float deltaTime();
	float getCurrentTime();
	float getElapsedTime();

	inline operator LuaUserdata<Timer>() {
		MAKE_LUA_INSTANCE_RET(Timer,ret);
		ret.Bind("deltaTime",&Timer::deltaTime);
		ret.Bind("runningTime",&Timer::getElapsedTime);

		return ret;
	}
};

#endif