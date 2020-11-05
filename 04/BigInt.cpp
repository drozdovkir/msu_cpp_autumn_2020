#include "BigInt.h"
#include <iostream>

BigInt::BigInt()
{
	size_ = 1;
	sign_ = false;
	digits_ = new int[size_];
	digits_[0] = 0;
}

BigInt::BigInt(int a)
{
	sign_ = false;
	
	if (a < 0)
	{
		sign_ = true;
		a = -a;
	}

	if (a == 0)
	{
		size_ = 1;
		digits_ = new int[size_];
		sign_ = false;
		digits_[0] = 0;
	}
	else
	{
		size_ = floor(log(a) / log(BASE)) + 1;
		digits_ = new int[size_];

		int i = 0;
		while (a > 0)
		{
			digits_[i] = a % BASE;
			a /= BASE;
			i++;
		}
	}
}

BigInt::BigInt(const std::string& s)
{	
	sign_ = s[0] == '-';
	int l = s.length() - (sign_ ? 1 : 0); // length of string excluding sign

	size_ = l / POWER + (l % POWER != 0 ? 1 : 0); // number of digits (assuming the input string is correct and doesn't have leading zeros)
	digits_ = new int[size_];

	int i = 0;
	int start = sign_ ? 1 : 0;

	int start_segment = s.length();
	int end_segment = 0;

	while (i < size_)
	{
		end_segment = start_segment - 1;
		start_segment = std::max(start, end_segment - POWER + 1);

		int a = 0;

		for (int v = start_segment; v <= end_segment; v++)
		{
			int d = s[v] - '0';
			a = 10 * a + d;
		}
		
		digits_[i] = a;
		i++;
	}
}

BigInt::BigInt(const BigInt& num): size_(num.size_), sign_(num.sign_)
{
	digits_ = new int[size_];

	for (int i = 0; i < size_; i++)
		digits_[i] = num.digits_[i];
}

BigInt::BigInt(BigInt&& num): size_(num.size_), sign_(num.sign_)
{
	digits_ = new int[size_];

	for (int i = 0; i < size_; i++)
		digits_[i] = num.digits_[i];

	num.digits_ = nullptr;
	num.size_ = 0;
}

BigInt& BigInt::operator =(int rhs)
{
	BigInt Rhs(rhs);
	*this = Rhs;

	return *this;
}

BigInt& BigInt::operator =(BigInt& rhs)
{
	if (this == &rhs)
		return *this;

	delete[] digits_;

	size_ = rhs.size_;
	sign_ = rhs.sign_;

	digits_ = new int[size_];

	for (int i = 0; i < size_; i++)
		digits_[i] = rhs.digits_[i];

	return *this;
}

BigInt& BigInt::operator =(BigInt&& rhs)
{
	if (this == &rhs)
		return *this;

	delete[] digits_;

	size_ = rhs.size_;
	sign_ = rhs.sign_;
	digits_ = rhs.digits_;

	rhs.digits_ = nullptr;
	rhs.size_ = 0;

	return *this;
}

// a + b (a, b > 0) and a - b (a > b, a,b > 0) cases are the only ones that implemented here
// Others can be expressed via them using the following rules:
//
// a + (-b) = a - b
// (-a) + b = b - a
// (-a) + (-b) = -(a + b)
//
// a - b = -(b - a) (a < b)
// a - (-b) = a + b
// (-a) - b = -(a + b)
// (-a) - (-b) = b - a

BigInt BigInt::operator +(int rhs)
{
	BigInt Rhs(rhs);
	return *this + Rhs;
}

BigInt BigInt::operator -(int rhs)
{
	BigInt Rhs(rhs);
	return *this - Rhs;
}

BigInt BigInt::operator *(int rhs)
{
	BigInt Rhs(rhs);
	return *this * Rhs;
}

BigInt BigInt::operator +(BigInt& rhs)
{
	if ((!sign_) && (rhs.sign_)) // a >= 0 and b < 0
	{
		BigInt result = (*this) - (-rhs);
		rhs = -rhs;
		return result;
	}

	if ((sign_) && (!rhs.sign_)) // a < 0 and b >= 0
	{
		BigInt result = rhs - (-(*this));
		*this = -(*this);
		return result;
	}

	if ((sign_) && (rhs.sign_)) // a < 0 and b < 0
	{
		BigInt result = -(-(*this) + (-rhs));
		*this = -(*this);
		rhs = -rhs;
		return result;
	}

	int remember = 0;
	int stop = std::max(size_, rhs.size_);
	int* digs = new int[stop + 1];

	for (int i = 0; i <= stop; i++)
	{
		int first_digit = i >= size_ ? 0 : digits_[i];
		int second_digit = i >= rhs.size_ ? 0 : rhs.digits_[i];
		int digits_sum = first_digit + second_digit + remember;

		remember = digits_sum / BASE;
		digs[i] = digits_sum % BASE;
	}

	stop = cut_zeros(digs, stop + 1);

	BigInt result;
	result.size_ = stop;
	result.digits_ = new int[result.size_];

	for (int i = 0; i < stop; i++)
		result.digits_[i] = digs[i];

	delete[] digs;
	return result;
}

BigInt BigInt::operator -(BigInt& rhs)
{
	if ((!sign_) && (rhs.sign_)) // a >= 0, b < 0
	{
		BigInt result = *this + (-rhs);
		rhs = -rhs;
		return result;
	}

	if ((sign_) && (!rhs.sign_)) // a < 0, b >= 0
	{
		BigInt result = -(-(*this) + rhs);
		*this = -(*this);
		return result;
	}

	if ((sign_) && (rhs.sign_)) // a < 0, b < 0
	{
		BigInt result = (-rhs) - (-(*this));
		*this = -(*this);
		rhs = -rhs;
		return result;
	}

	if (rhs > *this) // a < b
		return -(rhs - *this);


	// from now on a >= 0, b >= 0 and b > a
	int remember = 0;
	int stop = std::max(size_, rhs.size_);
	int* digs = new int[stop];

	for (int i = 0; i < stop; i++)
	{
		int first_digit = i >= size_ ? 0 : digits_[i];
		int second_digit = i >= rhs.size_ ? 0 : rhs.digits_[i];
		int digits_diff = first_digit - second_digit - remember;

		if (digits_diff < 0)
		{
			digits_diff = BASE + first_digit - second_digit - remember;
			remember = 1;
		}
		else
			remember = 0;

		digs[i] = digits_diff;
	}

	stop = cut_zeros(digs, stop);

	BigInt result;
	result.size_ = stop;
	result.sign_ = false;
	result.digits_ = new int[result.size_];

	for (int i = 0; i < stop; i++)
		result.digits_[i] = digs[i];

	delete[] digs;
	return result;
}

BigInt& BigInt::operator -()
{
	sign_ = !sign_;
	return *this;
}

BigInt BigInt::operator *(BigInt& rhs)
{
	if ((*this == 0) || (rhs == 0))
		return BigInt(0);

	int* digs_ = new int[size_ + rhs.size_];

	for (int k = 0; k < size_ + rhs.size_; k++)
		digs_[k] = 0;

	for (int i = 0; i < size_; i++)
	{
		long long remember = 0;

		for (int j = 0; j < rhs.size_; j++)
		{
			long long first_digit = digits_[i];
			long long second_digit = rhs.digits_[j];
			long long prod_digits = first_digit * second_digit + remember;

			long long sub_result = (long long)digs_[i + j] + (long long)(prod_digits % BASE);
			remember = prod_digits / BASE;

			digs_[i + j] = sub_result % BASE;
			remember += sub_result / BASE;
		}

		if (remember != 0)
			digs_[i + rhs.size_] += remember;
	}

	int stop = cut_zeros(digs_, size_ + rhs.size_);

	BigInt result;

	result.sign_ = !(((sign_) && (rhs.sign_)) || ((!sign_) && (!rhs.sign_))); // If signs of factors are different then -, otherwise +
	result.size_ = stop;

	result.digits_ = new int[result.size_];

	for (int k = 0; k < result.size_; k++)
		result.digits_[k] = digs_[k];

	delete[] digs_;
	return result;
}

// Only two operators among all can be implemented while other can be expressed via them
// Here == and < are implemented

bool BigInt::operator ==(int rhs) const
{
	BigInt Rhs(rhs);
	return *this == Rhs;
}

bool BigInt::operator !=(int rhs) const
{
	BigInt Rhs(rhs);
	return *this != Rhs;
}

bool BigInt::operator <=(int rhs) const
{
	BigInt Rhs(rhs);
	return *this <= Rhs;
}

bool BigInt::operator >=(int rhs) const
{
	BigInt Rhs(rhs);
	return *this >= Rhs;
}

bool BigInt::operator <(int rhs) const
{
	BigInt Rhs(rhs);
	return *this < Rhs;
}

bool BigInt::operator >(int rhs) const
{
	BigInt Rhs(rhs);
	return *this > Rhs;
}

bool BigInt::operator ==(BigInt& rhs) const
{
	if ((rhs.size_ != size_) || (rhs.sign_ != sign_)) // If signs or sizes are not equal then numbers are not equal as well
		return false;

	for (int i = 0; i < size_; i++)
		if (digits_[i] != rhs.digits_[i])
			return false;

	return true;
}

bool BigInt::operator !=(BigInt& rhs) const
{
	return !(*this == rhs);
}

bool BigInt::operator <=(BigInt& rhs) const
{
	return ((*this < rhs) || (*this == rhs));
}

bool BigInt::operator >=(BigInt& rhs) const
{
	return !(*this < rhs);
}

bool BigInt::operator <(BigInt& rhs) const
{
	if ((sign_) && (!rhs.sign_)) // If this number is negative and rhs is positive then this is smaller
		return true;
	if ((!sign_) && (rhs.sign_)) // Otherwise rhs is smaller
		return false;

	if (size_ > rhs.size_) // If this number is longer then it could be smaller only if it is negative
		return sign_;
	if (size_ < rhs.size_) // If this number is shorter then it could be smaller only if it is positive
		return !sign_;

	// Now both numbers have the same sign and size

	for (int i = size_ - 1; i >= 0; i--)
	{
		if (digits_[i] < rhs.digits_[i])
			return !sign_;
		if (digits_[i] > rhs.digits_[i])
			return sign_;
	}

	return false; // If numbers are equal this number is not smaller
}

bool BigInt::operator >(BigInt& rhs) const
{
	return !(*this <= rhs);
}

std::ostream& operator <<(std::ostream& out, const BigInt& num)
{
	out << num.digits_[num.size_ - 1] * (num.sign_ ? -1 : 1);

	for (int i = num.size_ - 2; i >= 0; i--)
	{
		int k = 0;
		if (num.digits_[i] == 0)
			k = 1;
		else
			k = (int)ceil(log10(num.digits_[i]));

		for (int j = POWER - k; j > 0; j--)
			out << 0;
		out << num.digits_[i];
	}

	return out;
}

BigInt::~BigInt()
{
	if (digits_ != nullptr)
		delete[] digits_;
}

int cut_zeros(int* arr, int size) // function to cut off leading zeros (actual for subtraction)
{
	int i = size - 1;

	for (; i > 0; i--)
		if (arr[i] != 0)
			return i + 1;

	return i + 1;
}