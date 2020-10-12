#pragma once
#include <cstdlib>

class MyAllocator
{
private:
	size_t memory_size_ = 0;
	char* begin_ = nullptr; // Pointer to the begining of the memory block
	char* current_ = nullptr; // Pointer to the begining of unused memory

public:
	// No constructor because make_allocator contains all its logic
	void make_allocator(size_t);
	char* alloc(size_t);
	void reset();
	~MyAllocator();
};