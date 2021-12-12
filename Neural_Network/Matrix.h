#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <functional>
class Matrix
{
private:
	float** matrix_data;
	int rows, columns;
	float sigmoid(const float x)const;
public:
	Matrix(int rows, int cols);
	Matrix(const Matrix& m);
	~Matrix();
	float getData(int i, int j)const;
	void setData(int i, int j, float data);
	void addData(int i, int j, float data);

	Matrix operator*(const Matrix& x)const;
	Matrix operator+(const Matrix& x)const;
	Matrix operator-(const Matrix& x)const;

	Matrix operator*(const float x)const;
	Matrix operator+(const float x)const;
	Matrix operator-(const float x)const;
	Matrix operator/(const float x)const;

	void operator+=(const float x);
	void operator-=(const float x);
	void operator*=(const float x);
	void operator/=(const float x);

	void operator=(const Matrix& x);
	float sigmoidDerivative(const float x)const;
	Matrix getSigmoidDerivative()const;
	Matrix getSigmoid()const;
	float inverseSigmoid(const float x)const;
	Matrix getInverseSigmoid()const;
	friend std::ostream& operator<<(std::ostream& os, const Matrix& Mat);
	void zero();
	void setRandom();
	int getColumns() const { return columns; }
	int getRows() const { return rows; }
	int getMax();
	float ReLU(const float x)const;
	float ReLUDerivative(const float x)const;
	float inverseReLU(const float x)const;
	Matrix getReLU()const;
	Matrix getReLUDerivative()const;
	Matrix getInverseReLU()const;
	Matrix applyFunction(std::function<float(const float&)> func);
};

#endif