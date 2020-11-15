#include "Formatter.h"
#include "BigInt.h"

#include <cassert>

int main()
{
	std::string s1 = format("Hello, {0}!", "World");
	assert(s1 == "Hello, World!"); // Simple test

	std::string s2 = format("I like {0} and {1}.", "apples", "C++");
	assert(s2 == "I like apples and C++."); // 2 arguments test

	std::string s3 = format("We don't {1} no {0}, we don't {1} no thought {2}.",
		"education", "need", "control");
	assert(s3 == "We don't need no education, we don't need no thought control."); // mixed order test

	std::string s4 = format("{7} {4} {3} {8} {5} {1}, {6} {9} {0} {2}.", 
		"to", "night", "fight", "is", "this", "first", "you", "If", "your", "have");
	assert(s4 == "If this is your first night, you have to fight."); // another one mixed order test

	std::string s5 = format("Time is a {0}.", "tool you can put on a wall or wear it on your wrist");
	assert(s5 == "Time is a tool you can put on a wall or wear it on your wrist."); // complex string test

	std::string s6 = format("Do you believe in {1}?", "me", "God", "potato");
	assert(s6 == "Do you believe in God?"); // extra arguments test

	std::string s7 = format("I'll take {0} stickers for {1} dollars.", 3, 0.5);
	assert(s7 == "I'll take 3 stickers for 0.5 dollars."); // integer and float arguments test

	// invalid expression in {} test
	int err = 10;
	try
	{
		std::string s8 = format("Just do {haha} and everyone will be happy!", "math");
		err = 0;
	}
	catch (const InvalidParanthesis& ex)
	{
		err = 1;
		std::cout << ex.what() << std::endl;
	}
	catch (const InvalidArguments& ex)
	{
		err = -1;
		std::cout << ex.what() << std::endl;
	}
	assert(err == 1);

	// no {} test
	err = 10;
	try
	{
		std::string s9 = format("I hurt myself today", "to", "see", "if", "I", "still", "feel");
		err = 0;
		assert(s9 == "I hurt myself today");
	}
	catch (const InvalidParanthesis& ex)
	{
		err = 1;
		std::cout << ex.what() << std::endl;
	}
	catch (const InvalidArguments& ex)
	{
		err = -1;
		std::cout << ex.what() << std::endl;
	}
	assert(err == 0);

	// wrong paranthesis order test
	err = 10;
	try
	{
		std::string s10 = format("You {0} should put } after {", "always");
		err = 0;
	}
	catch (const InvalidParanthesis& ex)
	{
		err = 1;
		std::cout << ex.what() << std::endl;
	}
	catch (const InvalidArguments& ex)
	{
		err = -1;
		std::cout << ex.what() << std::endl;
	}
	assert(err == 1);

	// } missing test
	err = 10;
	try
	{
		std::string s10 = format("I'll have {0 number nines, a number {1} large, a number {6} with extra {100}, a number {7}, two number 45s: {1} with cheese and a large soda",
			2, 9, 0, 0, 0, 0, 6, 7);
		err = 0;
	}
	catch (const InvalidParanthesis& ex)
	{
		err = 1;
		std::cout << ex.what() << std::endl;
	}
	catch (const InvalidArguments& ex)
	{
		err = -1;
		std::cout << ex.what() << std::endl;
	}
	assert(err == 1);
	
	// lack of arguments test
	err = 10;
	try
	{
		std::string s11 = format("I have witnessed events so {0} and so {1}, they could hardly be said to have occured at all",
			"tiny");
		err = 0;
	}
	catch (const InvalidParanthesis& ex)
	{
		err = 1;
		std::cout << ex.what() << std::endl;
	}
	catch (const InvalidArguments& ex)
	{
		err = -1;
		std::cout << ex.what() << std::endl;
	}
	assert(err == -1);

	// variables arguments test
	int a = 5;
	int b = 7;
	std::string s12 = format("{1} {0}", a, b);
	assert(s12 == "7 5");
	
	// User type arguments test
	BigInt num1("777777777777777777777777777777777777");
	BigInt num2("888888888888888888888888888888888888");
	std::string s13 = format("{0} * {1} = {2}", num1, num2, num1 * num2);
	assert(s13 == "777777777777777777777777777777777777 * 888888888888888888888888888888888888 = 691358024691358024691358024691358023308641975308641975308641975308641976");

	return 0;
}