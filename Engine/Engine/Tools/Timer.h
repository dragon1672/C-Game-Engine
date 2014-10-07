#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <windows.h>
#include <ExportHeader.h>
#include <Engine/Defines/SingletonsDefine.h>

class ENGINE_SHARED Timer {
private:
	LARGE_INTEGER _start;
	LARGE_INTEGER _stop;
	LARGE_INTEGER _lastInterval;
	LARGE_INTEGER total;//used for pause/resume
	LARGE_INTEGER frequency;
	float LargeInt2Secs( LARGE_INTEGER & L);

	float _deltaTime;

	DEFINE_SINGLETON(Timer);
public:
	Timer();
	void  start();
	float stop();
	void  pause();
	void  resume();
	float interval();
	float deltaTime();
	float getCurrentTime();
	float getElapsedTime();
};

#endif