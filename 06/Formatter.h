#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "FormatExceptions.h"

template <typename T>
void get_substrs(std::vector<std::string>& substrs_, const T& val)
{
	std::stringstream stream_;

	stream_ << val;  // Get string representation of argument and put it in a vector

	substrs_.push_back(stream_.str());
}

template <typename T, typename... argsT>
void get_substrs(std::vector<std::string>& substrs_, const T& val, const argsT&... args)
{
	std::stringstream stream_;

	stream_ << val;

	substrs_.push_back(stream_.str());

	get_substrs(substrs_, args...);
}

template <typename... argsT>
std::string format(const std::string& str, const argsT&... args)
{
	std::string res = ""; // Result string
	std::vector<std::string> substrs;

	bool inside_brackets = false;
	int start = 0;

	get_substrs(substrs, args...); // Create vector of arguments converted into strings

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
					
				int index = 0;
				std::string index_string = str.substr(start, v - start);
				try
				{
					index = std::stoi(index_string);
				}
				catch (const std::out_of_range& ex)
				{
					throw InvalidArguments(index_string, substrs.size());
				}

				if (index >= substrs.size())
					throw InvalidArguments(index_string, substrs.size());

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