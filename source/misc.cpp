#include <bitset>
#include "misc.hpp"

using namespace std;

string get_flags(uint16_t n)
{
	bitset<16> b(n);
	return b.to_string();
}

