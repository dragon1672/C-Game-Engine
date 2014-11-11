#pragma once

#include <ExportHeader.h>
#include <string>
#include <objbase.h>

class Stream;

class ENGINE_SHARED Object {
private:
	GUID id;
	std::string name;
public:
	Object(std::string name = "");
	virtual ~Object() {}
	double getID() const; //will be unique across all objects
	std::string Name() const;//can have dups
	void Name(const std::string name);

	friend ENGINE_SHARED Stream& operator<<(Stream& os, const Object& obj);
	friend ENGINE_SHARED Stream& operator>>(Stream& os,       Object& obj);

	static double GUID2Double(const GUID& guid);
	static GUID double2GIUD(const double d);
	static std::string GUID2string(const GUID& guid);

};

