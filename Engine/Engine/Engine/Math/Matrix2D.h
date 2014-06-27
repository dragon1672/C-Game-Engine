#pragma once
#ifndef MATRIX2D_H
#define MATRIX2D_H
#include "Vector 2.h"
#include <cmath>
class Matrix2D {
	float matrix[2][2];
public:
	Matrix2D() {
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++) {
				if(i==j) matrix[i][j] = 1;
				else     matrix[i][j] = 0;
			}
		}
	}
	Matrix2D(const Vector2D& row1, const Vector2D& row2) {
		matrix[0][0] = row1.getX();
		matrix[0][1] = row1.getY();
		matrix[1][0] = row2.getX();
		matrix[1][1] = row2.getY();
	}
	inline float get(int i, int j) const;
	inline Vector2D getRow(int i) const;
	inline Vector2D getCol(int j) const;
	inline static Matrix2D rotationMatrix(float angle);
	inline static Matrix2D transpose(Matrix2D max);
	inline static Matrix2D scaleX(float alpha);
	inline static Matrix2D scaleY(float alpha);
	inline static Matrix2D scale(float alpha);
	friend inline std::ostream& operator<<(std::ostream& stream, const Matrix2D& right);
	friend inline Matrix2D operator+ (const Matrix2D& left, const Matrix2D& right);
	friend inline Matrix2D operator- (const Matrix2D& left, const Matrix2D& right);
	friend inline Matrix2D operator* (const Matrix2D& left, const Matrix2D& right);
	friend inline Vector2D operator* (const Matrix2D& left, const Vector2D& right);
};
#include "Matrix2D.inl"
#endif