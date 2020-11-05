#include "BigInt.h"
#include <iostream>

BigInt factorial(int k)
{
	BigInt res(1);
	
	for (int i = 2; i <= k; i++)
		res = res * i;
	
	return res;
}

int main()
{
	std::cout << "Wanna calculate some factorial, but poor basic types don't allow you to do it?" << std::endl;
	std::cout << "Plug your number in here: ";
	
	int n = 0;
	
	std::cin >> n;
	
	BigInt F;
	F = factorial(n);
	
	std::cout << n << "! = ";
	std::cout << F << std::endl;
	
	return 0;
}