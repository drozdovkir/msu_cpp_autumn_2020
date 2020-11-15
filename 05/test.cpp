#include "Serializer.h"
#include "MyStruct.h"

#include <cassert>
#include <sstream>
#include <fstream>

int main()
{
	std::stringstream ss;
	std::string a, b, c;

	Serializer serializer1(ss);

	Data d1{ 1, false, 0 };
	serializer1.save(d1);

	ss >> a >> b >> c;

	assert(a == "1");
	assert(b == "false");
	assert(c == "0");

	Data d2{ 14, true, 15 };
	serializer1.save(d2);

	ss >> a >> b >> c;

	assert(a == "14");
	assert(b == "true");
	assert(c == "15");

	Data d3{ 1000, false, 0 };
	serializer1.save(d3);

	ss >> a >> b >> c;

	assert(a == "1000");
	assert(b == "false");
	assert(c == "0");

	Error error;
	Data d{ 0, false, 0 };

	std::stringstream ss1;
	Deserializer deserializer2(ss1);

	ss1 << "-1 false 1";
	error = deserializer2.load(d);
	assert(error == Error::CorruptedArchive);
	ss1.str("");

	ss1 << "1 true 123845934519237463957234679354729386545723674";
	error = deserializer2.load(d);
	assert(error == Error::CorruptedArchive);
	ss1.str("");

	std::ofstream test_ofile("tests.txt");

	Serializer serializer2(test_ofile);

	Data d8{ 12, true, 56 };
	Data d9{ 45, false, 5 };

	error = serializer2.save(d8);
	assert(error == Error::NoError);

	error = serializer2.save(d9);
	assert(error == Error::NoError);

	test_ofile.close();

	std::ifstream test_ifile("tests.txt");

	Deserializer deserializer3(test_ifile);

	error = deserializer3.load(d);
	assert(error == Error::NoError);
	assert(d.a == d8.a);
	assert(d.b == d8.b);
	assert(d.c == d8.c);

	error = deserializer3.load(d);
	assert(error == Error::NoError);
	assert(d.a == d9.a);
	assert(d.b == d9.b);
	assert(d.c == d9.c);

	test_ifile.close();

	return 0;
}