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
	Error process_(T val)
	{
		return put_value_<decltype(val)>(val);
	}

	template <typename T, typename... ArgsT>
	Error process_(T val, ArgsT... args)
	{
		Error err = put_value_<decltype(val)>(val);
		if (err != Error::NoError)
			return err;
		return process_(args...);
	}

	template <typename T>
	Error put_value_(T value)
	{
		return Error::CorruptedArchive;
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

template <>
Error Serializer::put_value_<bool>(bool value)
{
	out_ << std::boolalpha << value << separator;
	return Error::NoError;
}

template <>
Error Serializer::put_value_<uint64_t>(uint64_t value)
{
	out_ << value << separator;
	return Error::NoError;
}

class Deserializer
{
private:
	std::istream& in_;

	template <typename T>
	Error process_(T&& val)
	{
		std::string v;
		in_ >> v;
		return read_string_<decltype(val)>(v, val);
	}

	template <typename T, typename... ArgsT>
	Error process_(T&& val, ArgsT&&... args)
	{
		std::string v;
		in_ >> v;
		Error err = read_string_<decltype(val)>(v, val);
		if (err != Error::NoError)
			return err;
		return process_(std::forward<ArgsT>(args)...);
	}

	template <typename T>
	Error read_string_(const std::string& str, T& value)
	{
		return Error::CorruptedArchive;
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

template <>
Error Deserializer::read_string_<bool&>(const std::string& str, bool& value)
{
	if (str == "")
		return Error::CorruptedArchive;
	
	if (str == "true")
		value = true;
	else if (str == "false")
		value = false;
	else
		return Error::CorruptedArchive;

	return Error::NoError;
}

template <>
Error Deserializer::read_string_<uint64_t&>(const std::string& str, uint64_t& value)
{
	if (str == "")
		return Error::CorruptedArchive;
	
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