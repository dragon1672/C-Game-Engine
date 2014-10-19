#pragma once

#include <ExportHeader.h>

class ENGINE_SHARED Object {
private:
	static int GlobalID;
	int id;
protected:
	const char * name; // default nullptr
public:
	Object();
	int getID(); //will be unique across all objects
	const char * getName();//can have dups
};