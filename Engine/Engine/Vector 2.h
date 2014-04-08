#ifndef Vector2D_TWO
#define Vector2D_TWO
#include <iostream>
#include <cmath>
class Vector2D {
private:
	float x;
	float y;
public:
	explicit Vector2D(float x=0, float y=0) {
		this->x = x;
		this->y = y;
	}
	//getters
	inline float getX() const;
	inline float getY() const;
	//static non member declerations
	static inline float    dot          (const Vector2D&, const Vector2D&);
	static inline float    lengthSquared(const Vector2D&);
	static inline double   length       (const Vector2D&);
	static inline Vector2D normalized   (const Vector2D&);
	static inline Vector2D perpCW       (const Vector2D&);
	static inline Vector2D perpCCW      (const Vector2D&);
	static inline Vector2D LERP         (float, const Vector2D&, const Vector2D&);
	static inline float    cross        (const Vector2D&, const Vector2D&);
	static inline Vector2D projection   (const Vector2D& left, const Vector2D& right);
	static inline Vector2D rejection    (const Vector2D& left, const Vector2D& right);
	static inline bool     isZero       (const Vector2D& toCheck);
	//Member definitons
	inline float    lengthSquared() const;
	inline double   length() const;
	inline Vector2D normalized() const;
	inline Vector2D perpCW() const;
	inline Vector2D perpCCW() const;
	inline float    dot(const Vector2D& that) const;
	inline Vector2D LERP(float percent, const Vector2D& that) const;
	inline float    cross(const Vector2D& that) const;
	inline Vector2D projection(const Vector2D& that) const;
	inline Vector2D rejection (const Vector2D& that) const;
	inline bool     isZero() const;
	//overload declerations
	friend inline std::ostream& operator<<(std::ostream& stream, const Vector2D& right);
	friend inline Vector2D operator+ (const Vector2D& left, const Vector2D& right);
	friend inline Vector2D operator- (const Vector2D& left, const Vector2D& right);
	friend inline Vector2D operator- (const Vector2D& right);
	friend inline Vector2D operator* (const Vector2D& right, float constant       );
	friend inline Vector2D operator* (float constant,        const Vector2D& right);
	friend inline Vector2D operator/ (const Vector2D& right, float constant       );
	friend inline bool     operator==(const Vector2D& right, const Vector2D left  );
	inline operator float*();
};
//inlines
#include "Vector 2.inl"
#endif