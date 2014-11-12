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

	void Save(Stream& os);
	void Load(Stream& os);

	static double GUID2Double(const GUID& guid);
	static GUID double2GIUD(const double d);
	static std::string GUID2string(const GUID& guid);

};

