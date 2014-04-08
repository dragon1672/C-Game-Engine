#include "DebugTimer.h"

Timer DebugTimer::myTimer;
void  DebugTimer::init() {
	myTimer.start();
}
float DebugTimer::getTime() {
	return myTimer.getCurrentTime();
}
void  DebugTimer::shutdown() {
	myTimer.stop();
}