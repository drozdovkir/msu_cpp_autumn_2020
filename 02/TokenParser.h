#pragma once
#include <functional>
#include <cctype>
#include <string>
#include <vector>

enum TokenType
{
	digit,
	string
};

struct Token
{
	Token() {}
	Token(const std::string str, TokenType type_) { content = str; type = type_; }
	bool operator ==(const Token& rhs) const { return ((content == rhs.content) && (type == rhs.type)); }
	std::string content;
	TokenType type;
};

class TokenParser
{
private:
	std::vector<Token> tokens_;

	std::function<void()> start_func_;
	std::function<void(std::string&)> digit_func_;
	std::function<void(std::string&)> string_func_;
	std::function<void()> finish_func_;

	void default_start_handler_();
	void default_digit_token_handler_(std::string&);
	void default_string_token_handler_(std::string&);
	void default_finish_handler_();

	Token extract_token_(const std::string&, int&);

public:
	TokenParser();

	void set_start_callback(std::function<void()>);
	void set_digit_token_callback(std::function<void(std::string&)>);
	void set_string_token_callback(std::function<void(std::string&)>);
	void set_finish_callback(std::function<void()>);

	void process(const std::string&);
	std::vector<Token> get_tokens();
	void refresh();
};