#include "TokenParser.h"

void show_start_message()
{
	std::cout << "Preparing to parse the string" << std::endl;
}

void reverse_string(std::string& s)
{
	for (int i = 0; i < s.length() / 2; i++)
		std::swap(s[i], s[s.length() - i - 1]);
}

void increment(std::string& d)
{
	int i = d.length() - 1;

	while (d[i] == '9')
	{
		d[i] = '0';
		i--;
	}

	d[i]++;
}

void reduce_big_numbers(std::string& d)
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

	TokenParser tp1;

	// Without attached functions parsing goes well
	tp1.process(s1);
	tp1.print_tokens();
	tp1.refresh();

	tp1.process(s2);
	tp1.print_tokens();
	tp1.refresh();

	tp1.process(s3);
	tp1.print_tokens();
	tp1.refresh();

	TokenParser tp2;

	//User's functions can be attached to the object
	tp2.set_start_callback(show_start_message);
	tp2.set_digit_token_callback(increment);
	tp2.set_string_token_callback(reverse_string);
	tp2.set_finish_callback(show_finish_message);

	tp2.process(s1);
	tp2.print_tokens();
	tp2.refresh();

	tp2.process(s2);
	tp2.print_tokens();
	tp2.refresh();

	tp2.process(s3);
	tp2.print_tokens();
	tp2.refresh();

	TokenParser tp3;

	// User's functions can be replaced
	tp3.set_start_callback(show_start_message);
	tp3.set_finish_callback(show_finish_message);
	tp3.set_digit_token_callback(increment);

	tp3.process(s4);
	tp3.print_tokens();
	tp3.refresh();

	tp3.set_digit_token_callback(reduce_big_numbers);

	tp3.process(s4);
	tp3.print_tokens();
	tp3.refresh();

	TokenParser tp4;

	// Empty string can as well be parsed
	tp4.set_start_callback(show_start_message);
	tp4.set_finish_callback(show_finish_message);
	tp4.process(s5);
	tp4.print_tokens();

	return 0;
}