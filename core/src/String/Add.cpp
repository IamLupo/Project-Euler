#include "string.h"

long long IamLupo::String::addIntegers(const std::string &s) {
	int i, r;
	
	r = 0;
	
	for(i = 0; i < s.size(); i++)
		r += s[i] - 48;
	
	return r;
}