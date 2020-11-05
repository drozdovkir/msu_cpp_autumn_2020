#include "BigInt.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

int main()
{
	// Check int constructor
	BigInt n1(5);
	BigInt n2(0);
	BigInt n3(-2006);
	BigInt n4(1000000000);
	BigInt n5(999999999);
		
	int x = 10;
	BigInt n6(x);

	assert(n1 == 5);
	assert(n2 == 0);
	assert(n3 == -2006);
	assert(n4 == 1000000000);
	assert(n5 == 999999999);
	assert(n6 == 10);

	// Check string constructor
	BigInt s1("5");
	BigInt s2("0");
	BigInt s3("-1247534");
	BigInt s4("999999999");
	BigInt s5("1000000000");

	assert(s1 == 5);
	assert(s2 == 0);
	assert(s3 == -1247534);
	assert(s4 == 999999999);
	assert(s5 == 1000000000);

	// Check copy constructor
	BigInt c1(n3);

	assert(c1 == n3);

	// Check move constructor
	BigInt m1 = 54;
	BigInt m2 = std::move(m1);

	assert(m2 == 54);

	// Check int assignment
	BigInt a1;
	a1 = -12;

	assert(a1 == -12);

	// Check copy assignment
	BigInt a2;
	a2 = a1;

	assert(a2 == -12);

	// Check move assignment
	BigInt a3 = 65536;
	BigInt a4;

	a4 = std::move(a3);

	assert(a4 == 65536);

	// Check arithmetic operations
	BigInt r1 = n1 + n2;
	BigInt r2 = n4 + n5;
	BigInt r3 = n3 + n1;
	BigInt r4 = n2 + s3;

	assert(r1 == 5);
	assert(r2 == 1999999999);
	assert(r3 == -2001);
	assert(r4 == -1247534);

	BigInt r5 = n1 - n2;
	BigInt r6 = n3 - n4;
	BigInt r7 = s3 - n3;
	BigInt r8 = n6 - n3;

	assert(r5 == 5);
	assert(r6 == -1000002006);
	assert(r7 == -1247534 + 2006);
	assert(r8 == 2016);

	BigInt r9 = n1 * n6;
	BigInt r10 = n3 * n2;
	BigInt r11 = n2 * s2;
	BigInt r12 = n6 * n3;
	BigInt r13 = s3 * n6;
	BigInt r14 = n3 * a1;

	assert(r9 == 50);
	assert(r10 == 0);
	assert(r11 == 0);
	assert(r12 == -20060);
	assert(r13 == -12475340);
	assert(r14 == -2006 * (-12));
	
	std::ifstream sums_file("sums.txt");
	std::string line;

	while(std::getline(sums_file, line))
	{
		std::stringstream ss;
		ss << line;

		std::string sa;
		std::string sb;
		std::string sc;

		ss >> sa;
		ss >> sb;
		ss >> sc;

		BigInt a(sa);
		BigInt b(sb);
		BigInt c(sc);

		assert(a + b == c);
	}

	sums_file.close();

	std::ifstream diffs_file("diffs.txt");
	
	while (std::getline(diffs_file, line))
	{
		std::stringstream ss;
		ss << line;

		std::string sa;
		std::string sb;
		std::string sc;

		ss >> sa;
		ss >> sb;
		ss >> sc;

		BigInt a(sa);
		BigInt b(sb);
		BigInt c(sc);
		
		assert(a - b == c);
	}

	diffs_file.close();

	std::ifstream prods_file("prods.txt");

	while (std::getline(prods_file, line))
	{
		std::stringstream ss;
		ss << line;

		std::string sa;
		std::string sb;
		std::string sc;

		ss >> sa;
		ss >> sb;
		ss >> sc;

		BigInt a(sa);
		BigInt b(sb);
		BigInt c(sc);

		assert(a * b == c);
	}

	prods_file.close();
	
	BigInt e1 = 1;
	BigInt e2 = 0;
	BigInt e3 = 45;
	BigInt e4 = 20;
	BigInt e5 = -7;
	
	BigInt e6 = (e1 + e3) * 2 - e5 + e4 * e3;
	
	assert(e6 == 999);

	// Check boolean operators
	BigInt b1("37295347237641923641075263045873450663375437506974059874093772364283642523845347");
	BigInt b2("38725934857687485985704986740598688377289740330000000000000000000000000000000000");
	BigInt b3("832572345768943679743957");

	BigInt b4("-7342751345870847320344435807302733802020208734850237465747385743848303");
	BigInt b5("-1379624756239845762938476598236945945904509594309274589321747573674799");
	BigInt b6("-247692374623945769487");

	assert(b1 > 0);
	assert(!(b2 < 150));
	assert(!(b1 == 0));
	assert(b3 != -14);
	assert(b1 >= 0);
	assert(!(b2 <= -4));

	assert(!(b4 > 0));
	assert(b5 < 150);
	assert(!(b6 == 0));
	assert(b4 != -14);
	assert(!(b5 >= 0));
	assert(b6 <= -4);

	assert(!(b1 == b2));
	assert(b1 != b2);
	assert(b1 < b2);
	assert(!(b1 > b2));
	assert(b1 <= b2);
	assert(!(b1 >= b2));

	assert(b1 > b3);

	assert(!(b4 == b5));
	assert(b4 != b5);
	assert(b4 < b5);
	assert(!(b4 > b5));
	assert(b4 <= b5);
	assert(!(b4 >= b5));

	assert(b4 < b6);

	assert(b3 > b4);
	assert(b1 != b5);
	assert(b3 >= b6);
	assert(b4 <= b2);

	assert(b1 < b1 * b1);
	assert(b4 >= b4 * b4 * b5);


	// Check printing
	std::cout << b1 << std::endl;

	return 0;
}