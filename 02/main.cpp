#include "TokenParser.h"

int main()
{
	std::cout << "Enter string to parse" << std::endl;

	std::string input_string;
	std::getline(std::cin, input_string);

	TokenParser tparser;
	tparser.process(input_string);
	tparser.print_tokens();

	return 0;
}