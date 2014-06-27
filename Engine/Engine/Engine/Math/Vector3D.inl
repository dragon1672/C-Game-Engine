//getters
float Vector3D::getX() const { return x; }
float Vector3D::getY() const { return y; }
float Vector3D::getZ() const { return z; }
//static defines
float    Vector3D::lengthSquared(const Vector3D& src) {
	return dot(src,src);
}
double   Vector3D::length       (const Vector3D& src) {
	return sqrt(lengthSquared(src));
}
Vector3D Vector3D::normalized   (const Vector3D& src) {
	float Vlength = (float)length(src);
	return (Vlength==0)? Vector3D(0,0) : src/Vlength;
}
float    Vector3D::dot          (const Vector3D& left, const Vector3D& right) {
	return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
}
bool     Vector3D::isZero(const Vector3D& toCheck) {
	return (toCheck.x==0 && toCheck.y==0 && toCheck.z==0);
}
//member functions
float    Vector3D::lengthSquared() const {
	return lengthSquared(*this);
}
double   Vector3D::length() const {
	return length(*this);
}
Vector3D Vector3D::normalized() const {
	return normalized(*this);
}
float    Vector3D::dot(const Vector3D& that) const {
	return dot(*this,that);
}
bool     Vector3D::isZero() const {
	return isZero(*this);
}
//overloads
std::ostream& operator<<(std::ostream& stream, const Vector3D& right) {
	std::cout << "{" << right.x << ", " << right.y << "}";
	return stream;
}
Vector3D operator+ (const Vector3D& left,  const Vector3D& right) {
	return Vector3D(left.x + right.x, left.y + right.y, left.z + right.z);
}
Vector3D operator- (const Vector3D& left,  const Vector3D& right) {
	return Vector3D(left.x - right.x, left.y - right.y, left.z - right.z);
}
Vector3D operator- (const Vector3D& right) {
	return Vector3D(-right.x, -right.y, -right.z);
}
Vector3D operator* (const Vector3D& right, float constant) {
	return Vector3D(right.x * constant, right.y * constant, right.z * constant);
}
Vector3D operator* (float constant, const Vector3D& right) {
	return right * constant;
}
Vector3D operator/ (const Vector3D& right, float constant     ) {
	return Vector3D(right.x / constant, right.y / constant, right.z / constant);
}
bool     operator==(const Vector3D& right, const Vector3D left  ) {
	return (right.x==left.x && right.y==left.y && right.z==left.z);
}
Vector3D::operator float*() {
	return &x;
}