#include "TokenParser.h"
#include <iostream>

int main()
{
	std::cout << "Enter string to parse" << std::endl;

	std::string input_string;
	std::getline(std::cin, input_string);

	TokenParser tparser;
	tparser.process(input_string);
	std::vector<Token> tkns = tparser.get_tokens();

	for (int i = 0; i < tkns.size(); i++)
		std::cout << tkns[i].content << std::endl;

	return 0;
}