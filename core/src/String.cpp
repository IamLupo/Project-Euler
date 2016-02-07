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

std::vector<std::string>
IamLupo::String::explode(std::string const & s, char delim) {
	std::vector<std::string> result;
	std::istringstream iss(s);

	for (std::string token; std::getline(iss, token, delim);)
		result.push_back(std::move(token));

	return result;
}