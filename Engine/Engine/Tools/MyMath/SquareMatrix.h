#pragma once
#include <cmath>
#include <iostream>
#include <ctime>
double round(double val, int error) {
	int temp = (int)(val * (float)error);
	return (double)val/(double)error;
}

class SquareMatrix {
	double **matrix;
	int size;
	static const int MARGIN_OF_ERROR;
	void destory() {
		for(int i=0;i<size;i++) {
			delete [] matrix[i];
		}
		delete [] matrix;
	}
	
public:

	SquareMatrix(int size) {
		this->size = size;
		matrix = new double*[size];
		for(int i=0;i<size;i++) {
			matrix[i] = new double[size];
		}
	}
	~SquareMatrix() {
		std::cout << "bye bye matrix" << std::endl;
		destory();
	}
	int getSize() { return size; }
	double get(int i, int j) {
		return matrix[i][j];
	}
	void   set(double val, int i, int j) {
		matrix[i][j] = round(val,MARGIN_OF_ERROR);
	}
	SquareMatrix add(SquareMatrix& left, SquareMatrix& right) {
		int size = left.getSize();
        SquareMatrix newMatrix(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                double value = left.get(i, j) + right.get(i, j);
                newMatrix.set(value, i, j);
            }
        }
        return newMatrix;
	}
	SquareMatrix subtract(SquareMatrix& left, SquareMatrix& right) {
		int size = left.getSize();
        SquareMatrix newMatrix(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                double value = left.get(i, j) - right.get(i, j);
                newMatrix.set(value, i, j);
            }
        }
        return newMatrix;
	}
	SquareMatrix multiply(SquareMatrix& left, SquareMatrix& right) {
		int size = left.getSize();
        SquareMatrix newMatrix(size);
		for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                double value = 0;
                for (int k = 0; k < size; k++) {
                    value += left.get(i, k) * right.get(k, j);
                }
                newMatrix.set(value, i, j);
            }
        }
        return newMatrix;
	}
	SquareMatrix scale(SquareMatrix& left, double scale) {
		int size = left.getSize();
        SquareMatrix newMatrix(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                double value = left.get(i, j)*scale;
                newMatrix.set(value, i, j);
            }
        }
        return newMatrix;
	}
	SquareMatrix minor(SquareMatrix& max, int i, int j) {
		int size = max.getSize() - 1;
		SquareMatrix minor(size);
        int rowDiff = 0;
        for (int row = 0; row < size; row++) {
            int colDiff = 0;
            if (row == i) {
                rowDiff = 1;
            }
            for (int col = 0; col < size; col++) {
                if (col == j) {
                    colDiff = 1;
                }
                minor.set(max.get(row + rowDiff, col + colDiff), row, col);
            }

        }
        return minor;
	}
	double calcDetermant(SquareMatrix& max) {
		double result = 0;
		int size = max.getSize();
        if (size != 2) {
            for (int i = 0; i < size; i++) {
				SquareMatrix min = minor(max,0,i);
				double temp = calcDetermant(min);
                result += pow(-1, i) * max.get(0, i) * temp;
            }
        } else {
            result = max.get(0, 0) * max.get(1, 1) - max.get(0, 1) * max.get(1, 0);
        }
        return result;
	}
	SquareMatrix transpose(SquareMatrix& max) {
		int size = max.getSize();
        SquareMatrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.set(max.get(i, j), j, i);
            }
        }
        return result;
	}
	double coFactor(SquareMatrix& max, int i, int j) {
		return pow(-1, i + j) * calcDetermant(minor(max,i, j));
	}
	SquareMatrix adjoint(SquareMatrix& max) {
		int size = max.getSize();
		SquareMatrix result(size);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				result.set(coFactor(max, i, j), i, j);
			}
		}
		return transpose(result);
	}
	SquareMatrix inverse(SquareMatrix& max) {
		return scale(adjoint(max),1/calcDetermant(max));
	}
	bool hasInverse(SquareMatrix& max) {
		return calcDetermant(max)!=0;
	}
};
const int SquareMatrix::MARGIN_OF_ERROR = 10000;