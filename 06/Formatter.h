#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "FormatExceptions.h"

template <typename T>
void get_substrs(std::vector<std::string>& substrs_, T&& val)
{
	std::stringstream stream_;
	std::string s;

	stream_ << val;                 // Get string representation of argument
	std::getline(stream_, s);       // and put it in a vector

	substrs_.push_back(s);
}

template <typename T, typename... argsT>
void get_substrs(std::vector<std::string>& substrs_, T&& val, argsT&&... args)
{
	std::stringstream stream_;
	std::string s;

	stream_ << val;
	std::getline(stream_, s);

	substrs_.push_back(s);

	get_substrs(substrs_, std::forward<argsT>(args)...);
}

template <typename... argsT>
std::string format(const std::string& str, argsT&&... args)
{
	std::string res = ""; // Result string
	std::vector<std::string> substrs;

	bool inside_brackets = false;
	int start = 0;

	get_substrs(substrs, std::forward<argsT>(args)...); // Create vector of arguments converted into strings

	for (int v = 0; v < str.length(); v++)
	{
		if (!inside_brackets)
		{
			if (str[v] == '{')
			{
				inside_brackets = true;
				start = v + 1;
			}
			else
			{
				if (str[v] == '}') // '}' cannot be in front of '{'
					throw InvalidParanthesis("Invalid paranthesis order, { is missing");
				res += str[v];
			}
		}
		else
		{
			if (str[v] == '}')
			{
				if (v == start) // '{}' case
					throw InvalidParanthesis("Invalid expression indide {}, should be non-negative integer");

				int index = atoi(str.substr(start, v - start).c_str());

				if (index >= substrs.size())
					throw InvalidArguments(index, substrs.size());

				res += substrs[index];
				inside_brackets = false;
			}
			else
			{
				if (!isdigit(str[v])) // Only digits can be inside '{}'
					throw InvalidParanthesis("Invalid expression inside {}, should be non-negative integer");
			}
		}
	}

	if (inside_brackets) // If there is no '}' after parsing string
		throw InvalidParanthesis("Invalid paranthesis order: } is missing");

	return res;
}