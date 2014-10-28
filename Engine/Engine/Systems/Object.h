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
	int getID() const; //will be unique across all objects
	const char * Name() const;//can have dups
	void Name(const char * name);
};