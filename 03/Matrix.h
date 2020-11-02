#pragma once
#include <cstdlib>
#include <exception>
#include <iostream>

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
	int operator [](int) const;

	Vector& operator=(const Vector&);

	Vector& operator *=(int);
	Vector operator +(const Vector&) const;

	bool operator ==(const Vector&) const;
	bool operator !=(const Vector&) const;

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

	int get_rows() const;
	int get_columns() const;

	Vector& operator [](int);
	Vector operator [](int) const;

	Matrix& operator =(const Matrix&);

	Matrix& operator *=(int);
	Matrix operator +(const Matrix&) const;

	bool operator ==(const Matrix&) const;
	bool operator !=(const Matrix&) const;

	friend std::ostream& operator<< (std::ostream&, const Matrix&);

	~Matrix();
};