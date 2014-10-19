#pragma once

class Object {
private:
	int id;
protected:
	const char * name;
public:
	//should be unique
	int getID() { return id; }
	//can have dups
	virtual const char * getName() { return name; }
};