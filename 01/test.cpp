#include "MyAllocator.h"
#include <assert.h>

int main()
{
	MyAllocator myAllctr;

	// Allocator can be created and can allocate memory
	myAllctr.make_allocator(100);
	char* c = myAllctr.alloc(10);
	assert(c != nullptr);

	// Memory can be allocated one more time
	c = myAllctr.alloc(20);
	assert(c != nullptr);

	// Allocator cannot allocate memory that overcomes its capacity
	c = myAllctr.alloc(71);
	assert(c == nullptr);

	// Allocator can allocate exactly its size
	c = myAllctr.alloc(70);
	assert(c != nullptr);

	// After resetting big bunches of memory can be created again
	myAllctr.reset();
	c = myAllctr.alloc(80);
	assert(c != nullptr);

	// After creating new allocator memory is overwritten
	myAllctr.make_allocator(200);
	c = myAllctr.alloc(100);
	assert(c != nullptr);

	MyAllocator myAllctr2;

	// Memory cannot be allocated until allocator is created
	c = myAllctr2.alloc(10);
	assert(c == nullptr);

	// Reset works fine but cannot fix the problem
	myAllctr2.reset();
	myAllctr2.alloc(10);
	assert(c == nullptr);

	// After creating everything is OK
	myAllctr2.make_allocator(10);
	c = myAllctr2.alloc(10);
	assert(c != nullptr);

	return 0;
}