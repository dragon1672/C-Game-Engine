#pragma once
#ifndef LOG_DATA_H
#define LOG_DATA_H

#include "DebugTimer.h"

enum Severity { Info, Warning, Error, Severe };
#define MAX_SEVERITY Severe

/* Verbose Levels
 * 0 - prints the first instance of a log call Verbose 0
 * 1 - prints second instances of a log call Verbose 0 and all first instances of log call Verbose 1
 * 2-n Repeat pattern
 * second instance will automatically increment the passed verbosity level
//*/
struct LogData {
	LogData (Severity severity=Severity::Error,  std::string location="", int lineNumber=-1,         std::string message="", int verbosity=0)
		:    severity(severity),                 location(location),      lineNumber(lineNumber),    message(message),       verbosity(verbosity)
	{
		timestamp = GET_GLOBAL_TIME * 1000;//convert to miliseconds
	}
	Severity severity;
	std::string location;
	int         lineNumber;
	std::string message;
	int         verbosity;
	float       timestamp;
};

#endif