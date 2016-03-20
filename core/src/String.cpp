#include "IamLupo/string.h"

bool IamLupo::String::isPalindrome(long long n) {
	return IamLupo::String::isPalindrome(std::to_string(n));
}

bool IamLupo::String::isPalindrome(const std::string &s) {
	int i, l;
	
	l = s.size() - 1;
	
	for(i = 0; i < s.size() / 2; i++)
		if(s[i] != s[l - i])
			return false;
	
	return true;
}

bool IamLupo::String::common(const std::string &a, const std::string &b) {
	int i, j;
	bool f;
	
	for(i = 0; i < a.size(); i++) {
		f = false;
		
		for(j = 0; j < b.size() && !f; j++) {
			if(a[i] == b[j])
				f = true;
		}
		
		if(!f)
			return false;
	}
	
	for(i = 0; i < b.size(); i++) {
		f = false;
		
		for(j = 0; j < a.size() && !f; j++) {
			if(b[i] == a[j])
				f = true;
		}
		
		if(!f)
			return false;
	}
	
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


std::string IamLupo::String::binairy(int v) {
	std::string s;
	
	if(v == 0)
		s.push_back('0');
	
	while(v > 0) {
		s.push_back((v % 2 == 0) ? '0' : '1');
		v /= 2;
	}
	
	return s;
}
