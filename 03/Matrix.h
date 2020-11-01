#pragma once
#include <cstdlib>
#include <exception>
#include <iostream>

// Auxiliary class for Matrix implementation
class Vector
{
private:
	size_t size_;
	int* contents_;

public:
	Vector();
	Vector(size_t);
	Vector(const Vector&);

	int& operator [](int);

	Vector& operator=(const Vector&);

	Vector& operator *=(int);
	Vector operator +(const Vector&);

	bool operator ==(const Vector&);
	bool operator !=(const Vector&);

	friend std::ostream& operator<< (std::ostream&, const Vector&);

	~Vector();
};

class Matrix
{
private:
	size_t height_;
	size_t width_;

	Vector* contents_;

public:
	Matrix(size_t, size_t);
	Matrix(const Matrix&);

	int get_rows();
	int get_columns();

	Vector& operator [](int);

	Matrix& operator =(const Matrix&);

	Matrix& operator *=(int);
	Matrix operator +(const Matrix&);

	bool operator ==(const Matrix&);
	bool operator !=(const Matrix&);

	friend std::ostream& operator<< (std::ostream&, const Matrix&);

	~Matrix();
};