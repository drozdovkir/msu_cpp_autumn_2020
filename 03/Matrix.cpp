#include "Matrix.h"

Vector::Vector(): size_(0)
{
	contents_ = nullptr;
}

Vector::Vector(size_t size): size_(size)
{
	contents_ = new int[size_];
	
	for (int i = 0; i < size_; i++)
		contents_[i] = 0;
}

Vector::Vector(const Vector& v) : size_(v.size_)
{
	contents_ = new int[size_];

	for (int i = 0; i < size_; i++)
		contents_[i] = v.contents_[i];
}

int& Vector::operator [](int index)
{
	if ((index < 0) || (index >= size_))
		throw std::out_of_range("index is out of range");

	return contents_[index];
}

Vector& Vector::operator =(const Vector& v)
{
	size_ = v.size_;

	if (contents_ != nullptr)
		delete[] contents_;

	contents_ = new int[size_];

	for (int i = 0; i < size_; i++)
		contents_[i] = v.contents_[i];

	return *this;
}

Vector& Vector::operator *=(int k)
{
	for (int i = 0; i < size_; i++)
		contents_[i] *= k;
	return *this;
}

Vector Vector::operator +(const Vector& rhs)
{
	if (size_ != rhs.size_)
		throw std::out_of_range("sizes of operands are not equal");

	Vector result(size_);

	for (int i = 0; i < size_; i++)
		result.contents_[i] = contents_[i] + rhs.contents_[i];

	return result;
}

bool Vector::operator ==(const Vector& rhs)
{
	if (size_ != rhs.size_)
		return false;

	for (int i = 0; i < size_; i++)
		if (contents_[i] != rhs.contents_[i])
			return false;

	return true;
}

bool Vector::operator !=(const Vector& rhs)
{
	return !(*this == rhs);
}

std::ostream& operator<< (std::ostream& out, const Vector& v)
{
	for (int i = 0; i < v.size_; i++)
		out << v.contents_[i] << "\t";

	return out;
}

Vector::~Vector()
{
	delete[] contents_;
}

Matrix::Matrix(size_t rows, size_t cols): height_(rows), width_(cols)
{
	if ((height_ <= 0) || (width_ <= 0))
		throw std::out_of_range("incorrect parameter in constructor");

	contents_ = new Vector[height_];

	for (size_t i = 0; i < height_; i++)
		contents_[i] = Vector(width_);
}

Matrix::Matrix(const Matrix& m) : height_(m.height_), width_(m.width_)
{
	contents_ = new Vector[height_];

	for (int i = 0; i < height_; i++)
		contents_[i] = m.contents_[i];
}

int Matrix::get_rows()
{
	return height_;
}

int Matrix::get_columns()
{
	return width_;
}

Vector& Matrix::operator [](int index)
{
	if ((index < 0) || (index >= height_))
		throw std::out_of_range("index is out of range");

	return contents_[index];
}

Matrix& Matrix::operator =(const Matrix& rhs)
{
	if (this == &rhs)
		return *this;

	height_ = rhs.height_;
	width_ = rhs.width_;

	if (contents_ != nullptr)
		delete[] contents_;

	contents_ = new Vector[height_];

	for (int i = 0; i < height_; i++)
		contents_[i] = rhs.contents_[i];

	return *this;
}

Matrix& Matrix::operator *=(int k)
{
	for (int i = 0; i < height_; i++)
		contents_[i] *= k;
	return *this;
}

Matrix Matrix::operator +(const Matrix& rhs)
{
	if ((height_ != rhs.height_) || (width_ != rhs.width_))
		throw std::out_of_range("sizes of operands are not equal");

	Matrix result(height_, width_);

	for (int i = 0; i < height_; i++)
		result.contents_[i] = contents_[i] + rhs.contents_[i];

	return result;
}

bool Matrix::operator ==(const Matrix& rhs)
{
	if ((height_ != rhs.height_) || (width_ != rhs.width_))
		return false;

	for (int i = 0; i < height_; i++)
		if (contents_[i] != rhs.contents_[i])
			return false;

	return true;
}

bool Matrix::operator !=(const Matrix& rhs)
{
	return !(*this == rhs);
}

std::ostream& operator<< (std::ostream& out, const Matrix& m)
{
	for (int i = 0; i < m.height_; i++)
		out << m.contents_[i] << std::endl;

	return out;
}

Matrix::~Matrix()
{
	delete[] contents_;
}