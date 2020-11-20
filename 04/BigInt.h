#pragma once
#include <string>
#include <algorithm>
#include <cmath>

const int BASE = 1000 * 1000 * 1000; // Base of positional notation
const int POWER = (int)log10(BASE); // Number of digits in base of notation

class BigInt
{
private:
	int* digits_; // Digits representing number in positional notation with base = BASE
	int size_;
	bool sign_; // True if number is negative, false otherwise

public:
	BigInt();
	BigInt(int);
	BigInt(const std::string&);
	BigInt(const BigInt&);
	BigInt(BigInt&&);

	// Assignment operators
	BigInt& operator =(int);
	BigInt& operator =(const BigInt&);
	BigInt& operator =(BigInt&&);

	// Arithmetic operators
	BigInt operator +(int) const;
	BigInt operator -(int) const;
	BigInt operator *(int) const;

	BigInt operator +(const BigInt&) const;
	BigInt operator -(const BigInt&) const;
	BigInt operator *(const BigInt&) const;

	BigInt operator -() const;

	// Comparising operators
	bool operator ==(int) const;
	bool operator !=(int) const;
	bool operator <=(int) const;
	bool operator >=(int) const;
	bool operator <(int) const;
	bool operator >(int) const;

	bool operator ==(const BigInt&) const;
	bool operator !=(const BigInt&) const;
	bool operator <=(const BigInt&) const;
	bool operator >=(const BigInt&) const;
	bool operator <(const BigInt&) const;
	bool operator >(const BigInt&) const;

	friend std::ostream& operator <<(std::ostream&, const BigInt&);

	~BigInt();
};

int cut_zeros(int*, int);