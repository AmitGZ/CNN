#include "Matrix.h"
#include <iostream>
#include <Math.h>
#include <functional>

Matrix::Matrix(int rows, int cols)
{
	this->rows = rows;
	this->columns = cols;
	matrix_data = new float* [rows];
	for (int i = 0; i < rows;i++)
	{
		matrix_data[i] = new float[columns];
		for (int j = 0;j < columns;j++)
			matrix_data[i][j] = 0;
	}
}

Matrix::Matrix(const Matrix& m)
{
	this->rows = m.getRows();
	this->columns = m.getColumns();
	matrix_data = new float* [rows];
	for (int i = 0; i < rows;i++)
	{
		matrix_data[i] = new float[columns];
		for (int j = 0;j < columns;j++)
			matrix_data[i][j] = m.getData(i, j);
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
		delete[] matrix_data[i];
	delete[] matrix_data;
}


float Matrix::getData(int i, int j)const
{
	try
	{
		if (i >= rows || j >= columns || i < 0 || j < 0)
			throw 2;
		return matrix_data[i][j];
	}
	catch (int ex)
	{
		std::cout << "invalid matrix index" << std::endl;
	}
}

void Matrix::setData(int i, int j, float data)
{
	try
	{
		if (i >= rows || j >= columns || i < 0 || j < 0)
			throw 2;
		matrix_data[i][j] = data;
	}
	catch (int ex)
	{
		std::cout << "invalid matrix index" << std::endl;
	}
}

void Matrix::addData(int i, int j, float data)
{
	try
	{
		if (i >= rows || j >= columns || i < 0 || j < 0)
			throw 2;
		matrix_data[i][j] += data;
	}
	catch (int ex)
	{
		std::cout << "invalid matrix index" << std::endl;
	}
}


Matrix Matrix::operator*(const Matrix& x)const
{
	try
	{
		if (columns != x.getRows())
			throw x.getRows();

		Matrix product(rows, x.getColumns());

		for (int i = 0;i < rows;i++)
			for (int j = 0; j < x.getColumns();j++)
			{
				product.setData(i, j, 0);
				for (int k = 0; k < x.getRows();k++)
					product.addData(i, j, (matrix_data[i][k] * x.getData(k, j)));
			}
		return product;
	}
	catch (int ex) {
		std::cout << "can't multiply columns: " << columns << " rows: " << x.getRows() << std::endl;
	}
}

Matrix Matrix::operator+(const Matrix& x)const
{
	try
	{
		if (columns != x.getColumns() || rows != x.getRows())
			throw 3;

		Matrix sum(rows, columns);

		for (int i = 0;i < rows;i++)
			for (int j = 0; j < x.getColumns();j++)
				sum.setData(i, j, matrix_data[i][j] + x.getData(i, j));
		return sum;

	}
	catch (int ex) {
		std::cout << "can't add matrices exception: " << ex << std::endl;
	}
}

Matrix Matrix::operator-(const Matrix& x)const
{
	return (this->operator+ (x * -1));
}


Matrix Matrix::operator*(const float x)const
{
	Matrix tmp(rows, columns);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			tmp.setData(i, j, x * matrix_data[i][j]);
	return tmp;
}

Matrix Matrix::operator-(const float x)const
{
	return (this->operator+ (-x));
}

Matrix Matrix::operator/(const float x)const
{
	try
	{
		if (x == 0)
			throw 4;
		return this->operator*(1 / x);
	}
	catch (int ex)
	{
		std::cout << "divide by zero exception" << std::endl;
	}
}

Matrix Matrix::operator+(const float x)const
{
	Matrix tmp(rows, columns);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			tmp.setData(i, j, x + matrix_data[i][j]);
	return tmp;
}


void Matrix::operator*=(const float x)
{
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			setData(i, j, x * matrix_data[i][j]);
}

void Matrix::operator/=(const float x)
{
	try
	{
		if (x == 0)
			throw 4;
		this->operator*=(1 / x);
	}
	catch (int ex)
	{
		std::cout << "divide by zero exception" << std::endl;
	}
}

void Matrix::operator+=(const float x)
{
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			addData(i, j, x);
}

void Matrix::operator-=(const float x)
{
	this->operator+=(-x);
}

void Matrix::operator=(const Matrix& x)
{
	try
	{
		if (x.getRows() != rows || x.getColumns() != columns)
			throw 1;
		for (int i = 0;i < rows;i++)
			for (int j = 0;j < columns;j++)
				matrix_data[i][j] = x.getData(i, j);
	}
	catch (int ex)
	{
		std::cout << "invalid equal operationnon matching" << ex << std::endl;
	}
}


std::ostream& operator<<(std::ostream& os, const Matrix& Mat)
{
	for (int i = 0;i < Mat.getRows();i++)
	{
		for (int j = 0;j < Mat.getColumns();j++)
			os << i << "= " << Mat.getData(i, j) << '\t';
		os << '\n';
	}
	return os;

}

float Matrix::sigmoid(const float x)const
{
	return 1 / (1 + exp(-x));
}

float Matrix::sigmoidDerivative(const float x)const
{
	return sigmoid(x) * (1 - sigmoid(x));
}

float Matrix::inverseSigmoid(const float x)const
{
	return log(x / (1 - x));
}

float Matrix::ReLU(const float x)const
{
	return (x > 0) ? x : 0;
}

float Matrix::ReLUDerivative(const float x)const
{
	return x > 0 ? 1 : 0;
}

float Matrix::inverseReLU(const float x)const
{
	return (x > 0) ? x : 0;
}

Matrix Matrix::getReLU()const
{
	Matrix tmp(rows, columns);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			tmp.setData(i, j, ReLU(matrix_data[i][j]));
	return tmp;
}

Matrix Matrix::getReLUDerivative()const
{
	Matrix tmp(rows, columns);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			tmp.setData(i, j, ReLUDerivative(matrix_data[i][j]));
	return tmp;
}

Matrix Matrix::getInverseReLU()const
{
	Matrix tmp(rows, columns);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			tmp.setData(i, j, inverseReLU(matrix_data[i][j]));
	return tmp;
}


Matrix Matrix::getSigmoid()const
{
	Matrix tmp(rows, columns);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			tmp.setData(i, j, sigmoid(matrix_data[i][j]));
	return tmp;
}

Matrix Matrix::getSigmoidDerivative()const
{
	Matrix tmp(rows, columns);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			tmp.setData(i, j, sigmoidDerivative(matrix_data[i][j]));
	return tmp;
}

Matrix Matrix::getInverseSigmoid()const
{
	Matrix tmp(rows, columns);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			tmp.setData(i, j, inverseSigmoid(matrix_data[i][j]));
	return tmp;
}


void Matrix::zero()
{
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			setData(i, j, 0);
}

void Matrix::setRandom()
{
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			setData(i, j, (float)rand()/(RAND_MAX*10000));
}

int Matrix::getMax()
{
	int max = 0;
	for (int i = 0;i < rows;i++)
		if (getData(i, 0) >= getData(max, 0))
			max = i;
	return max;
}

Matrix Matrix::applyFunction(std::function<float(const float&)> func)
{
	Matrix tmp(rows, columns);
	for (int i = 0;i < rows;i++)
		for (int j = 0;j < columns;j++)
			tmp.setData(i, j, func(matrix_data[i][j]));
	return tmp;
}