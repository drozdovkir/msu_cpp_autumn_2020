#include <iostream>
#include "MyAllocator.h"

int main()
{
	MyAllocator myAllctr;

	myAllctr.make_allocator(100);

	char* c;
	c = myAllctr.alloc(10);

	myAllctr.reset();
	return 0;
}