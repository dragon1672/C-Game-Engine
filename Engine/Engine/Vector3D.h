#pragma once
#ifndef Vector3D_H
#define Vector3D_H
#include <iostream>
#include <cmath>
struct Vector3D {
private:
	float x;
	float y;
	float z;
public:
	explicit Vector3D(float x=0, float y=0, float z=0) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	//getters
	inline float getX() const;
	inline float getY() const;
	inline float getZ() const;
	//static non member declerations
	static inline float    dot          (const Vector3D&, const Vector3D&);
	static inline float    lengthSquared(const Vector3D&);
	static inline double   length       (const Vector3D&);
	static inline Vector3D normalized   (const Vector3D&);
	static inline bool     isZero       (const Vector3D& toCheck);
	//Member definitons
	inline float    dot(const Vector3D&) const;
	inline float    lengthSquared() const;
	inline double   length() const;
	inline Vector3D normalized() const;
	inline bool     isZero() const;
	//overload declerations
	friend inline std::ostream& operator<<(std::ostream& stream, const Vector3D& right);
	friend inline Vector3D operator+ (const Vector3D& left, const Vector3D& right);
	friend inline Vector3D operator- (const Vector3D& left, const Vector3D& right);
	friend inline Vector3D operator- (const Vector3D& right);
	friend inline Vector3D operator* (const Vector3D& right, float constant       );
	friend inline Vector3D operator* (float constant,        const Vector3D& right);
	friend inline Vector3D operator/ (const Vector3D& right, float constant       );
	friend inline bool     operator==(const Vector3D& right, const Vector3D left  );
	inline operator float*();
};
//inlines
#include "Vector3D.inl"
#endif