#include "get_flags.hpp"
#include <bitset>

string get_flags(uint16_t n)
{
	bitset<16> b(n);
	return b.to_string();
}

