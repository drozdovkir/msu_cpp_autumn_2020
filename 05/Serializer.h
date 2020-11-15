#pragma once
#include <iostream>
#include <string>
#include <climits>

enum class Error
{
	NoError,
	CorruptedArchive
};

class Serializer
{
	static constexpr char separator = ' ';

private:
	std::ostream& out_;

	template <typename T>
	Error process_(T&& val)
	{
		out_ << std::boolalpha << val << separator;
		return Error::NoError;
	}

	template <typename T, typename... ArgsT>
	Error process_(T&& val, ArgsT&&... args)
	{
		out_ << std::boolalpha << val << separator;
		return process_(std::forward<ArgsT>(args)...);
	}

public:
	explicit Serializer(std::ostream& out) : out_(out) {}

	template <typename T>
	Error save(T& object)
	{
		return object.serialize(*this);
	}

	template <typename... ArgsT>
	Error operator ()(ArgsT... args)
	{
		return process_(args...);
	}
};

class Deserializer
{
private:
	std::istream& in_;

	template <typename T>
	Error process_(T&& val)
	{
		std::string v;
		in_ >> v;
		return read_string_(v, val);
	}

	template <typename T, typename... ArgsT>
	Error process_(T&& val, ArgsT&&... args)
	{
		std::string v;
		in_ >> v;
		Error err = read_string_(v, val);
		if (err != Error::NoError)
			return err;
		return process_(std::forward<ArgsT>(args)...);
	}

	template <typename T>
	Error read_string_(const std::string& str, T& value)
	{
		if (str == "true")
			value = true;
		else
			if (str == "false")
				value = false;
			else
				return read_num_(str, value);

		return Error::NoError;
	}

	template <typename T>
	Error read_num_(const std::string& str, T& value)
	{
		uint64_t res = 0;

		for (int v = 0; v < str.length(); v++)
		{
			if ((str[v] == '.') || (!isdigit(str[v])))
				return Error::CorruptedArchive;

			if (res > (UINT_MAX - (str[v] - '0')) / 10)
				return Error::CorruptedArchive;

			res = 10 * res + (str[v] - '0');
		}

		value = res;
		return Error::NoError;
	}

public:
	explicit Deserializer(std::istream& in) : in_(in) {}

	template <typename T>
	Error load(T& object)
	{
		return object.deserialize(*this);
	}

	template <typename... ArgsT>
	Error operator()(ArgsT&... args)
	{
		return process_(args...);
	}
};