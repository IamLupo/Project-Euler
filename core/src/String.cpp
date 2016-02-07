#include "string.h"

long long IamLupo::String::addIntegers(const std::string &s) {
	int i, r;
	
	r = 0;
	
	for(i = 0; i < s.size(); i++)
		r += s[i] - 48;
	
	return r;
}

bool IamLupo::String::isPalindrome(const std::string &s) {
	int i, l;
	
	l = s.size() - 1;
	
	for(i = 0; i < s.size() / 2; i++)
		if(s[i] != s[l - i])
			return false;
	
	return true;
} 