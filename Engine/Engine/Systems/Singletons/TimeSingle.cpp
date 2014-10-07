#include "TimeSingle.h"
bool TimeSingle::startup()  { _timer.start(); return true; }
bool TimeSingle::shutdown() { _timer.stop(); return true; }
void TimeSingle::update()   { _timer.interval(); }
float TimeSingle::deltaTime()   { return _timer.deltaTime(); }
float TimeSingle::runningTime() { return _timer.stop(); }

IMPLEMENT_SINGLETON(TimeSingle);