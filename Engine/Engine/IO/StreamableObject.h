#pragma once

class Stream;

class StreamableObject {
public:
	virtual void Save(Stream&s) = 0;
	virtual void Load(Stream&s) = 0;
};