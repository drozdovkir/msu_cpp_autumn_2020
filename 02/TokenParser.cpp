#include "TokenParser.h"

TokenParser::TokenParser()
{
	start_func_ = finish_func_ = nullptr;
	digit_func_ = string_func_ = nullptr;
}

void TokenParser::set_start_callback(std::function<void()> func)
{
	start_func_ = func;
}

void TokenParser::set_digit_token_callback(std::function<void(std::string&)> func)
{
	digit_func_ = func;
}

void TokenParser::set_string_token_callback(std::function<void(std::string&)> func)
{
	string_func_ = func;
}

void TokenParser::set_finish_callback(std::function<void()> func)
{
	finish_func_ = func;
}

void TokenParser::process(const std::string& str)
{
	Token current_token;
	int v = 0;

	default_start_handler_();

	while (v < str.length())
	{
		current_token = extract_token_(str, v);

		if (current_token.type == digit)
			default_digit_token_handler_(current_token.content);
		else
			default_string_token_handler_(current_token.content);

		tokens_.push_back(current_token);
	}

	default_finish_handler_();
}

std::vector<Token> TokenParser::get_tokens()
{
	return tokens_;
}

void TokenParser::refresh()
{
	tokens_.clear();
}

void TokenParser::default_start_handler_()
{
	if (start_func_ != nullptr)
		start_func_();
}

void TokenParser::default_digit_token_handler_(std::string& tkn)
{
	if (digit_func_ != nullptr)
		digit_func_(tkn);
}

void TokenParser::default_string_token_handler_(std::string& tkn)
{
	if (string_func_ != nullptr)
		string_func_(tkn);
}

void TokenParser::default_finish_handler_()
{
	if (finish_func_ != nullptr)
		finish_func_();
}

Token TokenParser::extract_token_(const std::string& str, int& v)
{
	Token result_token;
	result_token.type = digit;

	for (int i = v; ; i++)
		if (isspace(str[i]) || (str[i] == '\0'))
		{
			result_token.content = str.substr(v, i - v);
			v = i + 1;
			break;
		}
		else if (!isdigit(str[i]))
			result_token.type = string;

	return result_token;
}