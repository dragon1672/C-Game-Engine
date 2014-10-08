Vector3D Matrix3D::getRow(int i) const {
	return Vector3D(matrix[i][0],matrix[i][1],matrix[i][2]);
}
Vector3D Matrix3D::getCol(int j) const {
	return Vector3D(matrix[0][j],matrix[1][j],matrix[2][j]);
}
Matrix3D Matrix3D::rotationMatrix(float angle) {
	Vector3D rowOne(cos(angle),-sin(angle),0);
	Vector3D rowTwo(sin(angle),cos(angle),0);
	Vector3D rowThree(0,0,1);
	return Matrix3D(rowOne,rowTwo,rowThree);
}
Matrix3D Matrix3D::rotateToVector(Vector2D src) {
	Vector2D perp = src.perpCW();
	Vector3D rowOne(perp.getX(),src.getX(),0);
	Vector3D rowTwo(perp.getY(),src.getY(),0);
	Vector3D rowThree(0,0,1);
	return Matrix3D(rowOne,rowTwo,rowThree);
}
Matrix3D Matrix3D::scaleX(float alpha) {
	Vector3D rowOne(alpha,0,0);
	Vector3D rowTwo(0,1,0);
	Vector3D rowThree(0,0,1);
	return Matrix3D(rowOne,rowTwo,rowThree);
}
Matrix3D Matrix3D::scaleY(float alpha) {
	Vector3D rowOne(1,0,0);
	Vector3D rowTwo(0,alpha,0);
	Vector3D rowThree(0,0,1);
	return Matrix3D(rowOne,rowTwo,rowThree);
}
Matrix3D Matrix3D::scale(float alpha) {
	Vector3D rowOne(alpha,0,0);
	Vector3D rowTwo(0,alpha,0);
	Vector3D rowThree(0,0,1);//because these matrix's are for modifying 2d vectors
	return Matrix3D(rowOne,rowTwo,rowThree);
}
Matrix3D Matrix3D::translate(float x, float y) {
	Vector3D rowOne(1,0,x);
	Vector3D rowTwo(0,1,y);
	Vector3D rowThree(0,0,1);
	return Matrix3D(rowOne,rowTwo,rowThree);
}
Matrix3D Matrix3D::translate(const Vector2D& toTrans) {
	return translate(toTrans.getX(),toTrans.getY());
}
std::ostream& operator<<(std::ostream& stream, const Matrix3D& max) {
	std::cout << "{ {" << max.get(0,0) << ", " << max.get(0,1) << "}, {" << max.get(1,0) << ", " << max.get(1,1) << "} }";
	return stream;
}
inline Matrix3D operator+ (const Matrix3D& left, const Matrix3D& right) {
	Vector3D row1 = left.getRow(0) + right.getRow(0);
	Vector3D row2 = left.getRow(0) + right.getRow(0);
	Vector3D row3 = left.getRow(0) + right.getRow(0);
	return Matrix3D(row1,row2,row3);
}
inline Matrix3D operator- (const Matrix3D& left, const Matrix3D& right) {
	Vector3D row1 = left.getRow(0) - right.getRow(0);
	Vector3D row2 = left.getRow(0) - right.getRow(0);
	Vector3D row3 = left.getRow(0) - right.getRow(0);
	return Matrix3D(row1,row2,row3);
}
inline Matrix3D operator* (const Matrix3D& left, const Matrix3D& right) {
	Matrix3D result;
	for(int i=0;i<MATRIX3D_LENGTH;i++) {
		for(int j=0;j<MATRIX3D_LENGTH;j++) {
			result.matrix[i][j] = left.getRow(i).dot(right.getCol(j));
		}
	}
	return result;
}
inline Vector3D operator* (const Matrix3D& left, const Vector3D& right) {
	float x = left.getRow(0).dot(right);
	float y = left.getRow(1).dot(right);
	float z = left.getRow(2).dot(right);
	return Vector3D(x,y,z);
}
inline Vector2D operator* (const Matrix3D& left, const Vector2D& right) {
	Vector3D ret = left * Vector3D(right.getX(),right.getY(),1);
	return Vector2D(ret.getX(),ret.getY());
}
Matrix3D::operator float*() {
	return reinterpret_cast<float*>(matrix);
}