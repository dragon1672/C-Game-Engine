#include "Timer.h"
#include <windows.h>


float Timer::LargeInt2Secs( LARGE_INTEGER & L) {
	return ((float)L.QuadPart / (float)frequency.QuadPart);
}
      Timer::Timer() {
	_start.QuadPart = 0;
	_stop.QuadPart  = 0;
	total.QuadPart = 0;
	QueryPerformanceFrequency(&frequency);//setting the freq
}
void  Timer::start() {
	total.QuadPart = 0;
	QueryPerformanceCounter(&_start);
	QueryPerformanceCounter(&_lastInterval);
}
float Timer::stop() {
	QueryPerformanceCounter(&_stop);
	return getElapsedTime();
}
void  Timer::pause() {
	QueryPerformanceCounter(&_stop);
	total.QuadPart += _stop.QuadPart - _start.QuadPart;
}
void  Timer::resume() {
	QueryPerformanceCounter(&_start);
}
float Timer::interval() {
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);
	LARGE_INTEGER TEMP;
	TEMP.QuadPart = current.QuadPart - _lastInterval.QuadPart;
	_lastInterval = current;
	return LargeInt2Secs(TEMP);
}
float Timer::getCurrentTime() {
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);
	LARGE_INTEGER TEMP;
	TEMP.QuadPart = current.QuadPart - _start.QuadPart;
	return LargeInt2Secs(TEMP);
}
float Timer::getElapsedTime() {
	LARGE_INTEGER TEMP;
	TEMP.QuadPart = total.QuadPart + _stop.QuadPart - _start.QuadPart;
	return LargeInt2Secs(TEMP);
}