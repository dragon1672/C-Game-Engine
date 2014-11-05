#pragma once

#include <ExportHeader.h>
#include <string>

class ENGINE_SHARED Object {
private:
	static int GlobalID;
	int id;
protected:
	std::string name;
public:
	Object();
	virtual ~Object() {}
	int getID() const; //will be unique across all objects
	std::string Name() const;//can have dups
	void Name(const std::string name);
};