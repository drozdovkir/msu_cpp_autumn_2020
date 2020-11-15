#include "Formatter.h"

#include <cassert>

int main()
{
	auto text = format("{1}+{1} = {0}", 2, "one");
	assert(text == "one+one = 2");
}