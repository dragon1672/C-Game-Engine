#pragma once

class BoundFloat {
	float& ref;
public:
	BoundFloat(float& toWatch) : ref(toWatch) {}
	BoundFloat(float * toWatch) : ref(*toWatch) {}
	BoundFloat& operator=(const float& that) { ref = that; return *this; }
	inline operator float&() { return ref; }
};