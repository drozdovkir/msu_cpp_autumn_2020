#include "MyAllocator.h"

void MyAllocator::make_allocator(size_t max_size)
{
	// If allocator already exists reallocate memory, otherwise allocate new block
	if (begin_ != nullptr)
		begin_ = static_cast<char*>(realloc(begin_, max_size));
	else
		begin_ = static_cast<char*>(malloc(max_size));

	current_ = begin_;

	if (begin_ != nullptr)
		memory_size_ = max_size;
}

char* MyAllocator::alloc(size_t size_)
{
	// If allocator was not created or required memory size overcomes availible limit then do nothing
	if ((begin_ == nullptr) || (current_ + size_ > begin_ + memory_size_))
		return nullptr;

	char* result = current_;
	current_ += size_;

	return result;
}

void MyAllocator::reset()
{
	current_ = begin_;
}

MyAllocator::~MyAllocator()
{
	if (begin_ != nullptr)
		free(begin_);
}