#pragma once
#include <exception>
#include <string>

// Exception thrown when syntax of {n} is broken
class InvalidParanthesis : public std::exception
{
private:
	std::string error_message_;
public:
	InvalidParanthesis(std::string err_mes): error_message_(err_mes) {}
	const char* what() const noexcept override { return error_message_.c_str(); }
};

// Exception thrown when mismatch between amount of arguments and positions occurs
class InvalidArguments : public std::exception
{
private:
	int arg_index_;
	int arg_size_;
public:
	InvalidArguments(int i, int size): arg_index_(i), arg_size_(size) {}
	const char* what() const noexcept override
	{
		std::stringstream ss;
		ss << "Invalid count of arguments: " << arg_index_ << " positional arguments required, but only "
			<< arg_size_ << " given";

		return (ss.str()).c_str();
	}
};