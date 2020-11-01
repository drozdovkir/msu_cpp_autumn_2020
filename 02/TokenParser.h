#pragma once
#include <iostream>
#include <string>
#include <vector>

enum TokenType
{
	digit,
	string
};

struct Token
{
	std::string content;
	TokenType type;
};

class TokenParser
{
private:
	std::vector<Token> tokens_;

	void(*start_func_)();
	void(*digit_func_)(std::string&);
	void(*string_func_)(std::string&);
	void(*finish_func_)();

	void default_start_handler_();
	void default_digit_token_handler_(std::string&);
	void default_string_token_handler_(std::string&);
	void default_finish_handler_();

	Token extract_token_(std::string&, int&);

public:
	TokenParser();

	void set_start_callback(void(*func)());
	void set_digit_token_callback(void(*func)(std::string&));
	void set_string_token_callback(void(*func)(std::string&));
	void set_finish_callback(void(*func)());

	void process(std::string&);
	void print_tokens();
	void refresh();
};