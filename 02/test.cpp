#include "TokenParser.h"
#include <iostream>
#include <fstream>
#include <cassert>

void show_start_message()
{
	std::cout << "Preparing to parse the string" << std::endl;
}

void reverse_string(std::string& s)
{
	for (int i = 0; i < s.length() / 2; i++)
		std::swap(s[i], s[s.length() - i - 1]);
}

void increment(std::string& d) // increment string number
{
	int i = d.length() - 1;

	while (d[i] == '9')
	{
		d[i] = '0';
		i--;
	}

	d[i]++;
}

void reduce_big_numbers(std::string& d) // Replace all numbers with length > 3 to "many"
{
	if (d.length() > 3)
		d = "many";
}

void show_finish_message()
{
	std::cout << "Parsing is done" << std::endl;
}

int main()
{
	std::string s1 = "This is example string number 1";
	std::string s2 = "This	is	example	string	number	2";
	std::string s3 = "This\nis\nexample\nstring\nnumber\n3";

	std::string s4 = "I have 3 sweets and my brother has 65536 sweets";
	std::string s5 = "";

	std::vector<Token> tokens1 = { 
		Token("This", string),
		Token("is", string),
		Token("example", string),
		Token("string", string),
		Token("number", string),
		Token("1", digit)
	};

	std::vector<Token> tokens2 = {
		Token("This", string),
		Token("is", string),
		Token("example", string),
		Token("string", string),
		Token("number", string),
		Token("2", digit)
	};

	std::vector<Token> tokens3 = {
		Token("This", string),
		Token("is", string),
		Token("example", string),
		Token("string", string),
		Token("number", string),
		Token("3", digit)
	};

	std::vector<Token> tokens1_changed = {
		Token("sihT", string),
		Token("si", string),
		Token("elpmaxe", string),
		Token("gnirts", string),
		Token("rebmun", string),
		Token("2", digit)
	};

	std::vector<Token> tokens2_changed = {
		Token("sihT", string),
		Token("si", string),
		Token("elpmaxe", string),
		Token("gnirts", string),
		Token("rebmun", string),
		Token("3", digit)
	};

	std::vector<Token> tokens3_changed = {
		Token("sihT", string),
		Token("si", string),
		Token("elpmaxe", string),
		Token("gnirts", string),
		Token("rebmun", string),
		Token("4", digit)
	};

	std::vector<Token> tokens4 = {
		Token("I", string),
		Token("have", string),
		Token("3", digit),
		Token("sweets", string),
		Token("and", string),
		Token("my", string),
		Token("brother", string),
		Token("has", string),
		Token("65536", digit),
		Token("sweets", string)
	};

	std::vector<Token> tokens4_changed = {
		Token("I", string),
		Token("have", string),
		Token("3", digit),
		Token("sweets", string),
		Token("and", string),
		Token("my", string),
		Token("brother", string),
		Token("has", string),
		Token("many", digit),
		Token("sweets", string)
	};

	// Parser can perform its behaviour without callbacks attachment
	TokenParser tp1;

	tp1.process(s1);
	std::vector<Token> result1 = tp1.get_tokens();
	tp1.refresh();

	tp1.process(s2);
	std::vector<Token> result2 = tp1.get_tokens();
	tp1.refresh();

	tp1.process(s3);
	std::vector<Token> result3 = tp1.get_tokens();
	tp1.refresh();

	assert(result1 == tokens1);
	assert(result2 == tokens2);
	assert(result3 == tokens3);

	// User's callbacks can be attached and parse tokens
	TokenParser tp2;

	tp2.set_start_callback(show_start_message);
	tp2.set_string_token_callback(reverse_string);
	tp2.set_digit_token_callback(increment);
	tp2.set_finish_callback(show_finish_message);

	tp2.process(s1);
	std::vector<Token> result4 = tp2.get_tokens();
	tp2.refresh();

	tp2.process(s2);
	std::vector<Token> result5 = tp2.get_tokens();
	tp2.refresh();

	tp2.process(s3);
	std::vector<Token> result6 = tp2.get_tokens();
	tp2.refresh();

	assert(result4 == tokens1_changed);
	assert(result5 == tokens2_changed);
	assert(result6 == tokens3_changed);

	// User's callbacks can be attached at any time after creating TokenParser object
	// Each string can be parsed as many times as needed
	TokenParser tp3;

	tp3.set_start_callback(show_start_message);
	tp3.set_finish_callback(show_finish_message);

	tp3.process(s4);
	std::vector<Token> result7 = tp3.get_tokens();
	tp3.refresh();

	tp3.set_digit_token_callback(reduce_big_numbers);

	tp3.process(s4);
	std::vector<Token> result8 = tp3.get_tokens();
	tp3.refresh();

	assert(result7 == tokens4);
	assert(result8 == tokens4_changed);

	// Parsing empty string is OK
	TokenParser tp4;

	tp4.process(s5);

	assert(tp4.get_tokens().empty());

	// Finding all numbers in text file
	TokenParser tp5;

	std::ifstream text_file("whales.txt"); // File with text about whales
	std::ifstream answer_file("whales_ans.txt"); // File with all numbers (surrounded by space symbols) from whales.txt
	
	std::string text;
	std::string answer;

	while (getline(text_file, text))
		tp5.process(text);
	
	std::vector<Token> tokens = tp5.get_tokens();
	tp5.refresh();
	
	while (getline(answer_file, answer))
		tp5.process(answer);
	
	std::vector<Token> digit_tokens = tp5.get_tokens();
	tp5.refresh();
	
	text_file.close();
	answer_file.close();

	std::vector<Token> result;

	for (int i = 0; i < tokens.size(); i++)
		if (tokens[i].type == digit)
			result.push_back(tokens[i]);

	assert(result == digit_tokens);

	return 0;
}