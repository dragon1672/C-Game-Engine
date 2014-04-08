float    Matrix2D::get(int i, int j) const {
	return matrix[i][j];
}
Vector2D Matrix2D::getRow(int i) const {
	return Vector2D(matrix[i][0],matrix[i][1]);
}
Vector2D Matrix2D::getCol(int j) const {
	return Vector2D(matrix[0][j],matrix[1][j]);
}
Matrix2D Matrix2D::rotationMatrix(float angle) {
	Vector2D rowOne(cos(angle),-sin(angle));
	Vector2D rowTwo(sin(angle),cos(angle));
	return Matrix2D(rowOne,rowTwo);
}
Matrix2D Matrix2D::transpose(Matrix2D max) {
	Vector2D rowOne(max.get(0,0),max.get(1,0));
	Vector2D rowTwo(max.get(0,1),max.get(1,1));
	return Matrix2D(rowOne,rowTwo);
}
Matrix2D Matrix2D::scaleX(float alpha) {
	Vector2D rowOne(alpha,0);
	Vector2D rowTwo(0,1);
	return Matrix2D(rowOne,rowTwo);
}
Matrix2D Matrix2D::scaleY(float alpha) {
	Vector2D rowOne(1,0);
	Vector2D rowTwo(0,alpha);
	return Matrix2D(rowOne,rowTwo);
}
Matrix2D Matrix2D::scale(float alpha) {
	Vector2D rowOne(alpha,0);
	Vector2D rowTwo(0,alpha);
	return Matrix2D(rowOne,rowTwo);
}

std::ostream& operator<<(std::ostream& stream, const Matrix2D& max) {
	std::cout << "{ {" << max.get(0,0) << ", " << max.get(0,1) << "}, {" << max.get(1,0) << ", " << max.get(1,1) << "} }";
	return stream;
}
inline Matrix2D operator+ (const Matrix2D& left, const Matrix2D& right) {
	Vector2D rowOne(left.get(0,0)+right.get(0,0),left.get(0,1)+right.get(0,1));
	Vector2D rowTwo(left.get(1,0)+right.get(1,0),left.get(1,1)+right.get(1,1));
	return Matrix2D(rowOne,rowTwo);
}
inline Matrix2D operator- (const Matrix2D& left, const Matrix2D& right) {
	Vector2D rowOne(left.get(0,0)-right.get(0,0),left.get(0,1)-right.get(0,1));
	Vector2D rowTwo(left.get(1,0)-right.get(1,0),left.get(1,1)-right.get(1,1));
	return Matrix2D(rowOne,rowTwo);
}
inline Matrix2D operator* (const Matrix2D& left, const Matrix2D& right) {
	Matrix2D result;
	for(int i=0;i<2;i++) {
		for(int j=0;j<2;j++) {
			result.matrix[i][j] = left.getRow(i).dot(right.getCol(j));
		}
	}
	return result;
}
inline Vector2D operator* (const Matrix2D& left, const Vector2D& right) {
	float x = left.getRow(0).dot(right);
	float y = left.getRow(1).dot(right);
	return Vector2D(x,y);
}