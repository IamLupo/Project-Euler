#include <math.h>

#include "IamLupo/number.h"

long long IamLupo::Number::to(const std::vector<int> &v) {
	int i;
	long long r;
	
	r = 0;
	
	for(i = v.size(); i > 0; i--)
		r += v[i - 1] * pow(10, i - 1);
	
	return r;
}

long long IamLupo::Number::to(const std::set<int> &v) {
	int i;
	long long r;
	std::set<int>::iterator it;
	
	i = v.size();
	r = 0;
	
	for(it = v.begin(); it != v.end(); ++it) {
		r += *it * pow(10, i - 1);
		i--;
	}
	
	return r;
}

long long IamLupo::Number::to(const std::string &s) {
	int i, p;
	long long r;
	
	p = 0;
	r = 0;
	
	for(i = s.size(); i > 0; i--) {
		if(s[i - 1] >= 0x30 && s[i - 1] <= 0x39) {
			r += (s[i - 1] - 0x30) * pow(10, p);
			p++;
		}
	}
	
	return r;
}

long long IamLupo::Number::sum(const std::string &s) {
	int i;
	long long r;
	
	r = 0;
	
	for(i = 0; i < s.size(); i++)
		r += s[i] - 48;
	
	return r;
}

long long IamLupo::Number::sum(const std::vector<int> &v) {
	int i;
	long long r;
	
	r = 0;
	
	for(i = 0; i < v.size(); i++)
		r += v[i];
	
	return r;
}

/*
	It will give the next base number of a value

	Example:
		f(5) = 10
		f(9) = 10
		f(11) = 100
		f(55) = 100
		f(101) = 1000
*/
long long IamLupo::Number::nextBase(int b, int v) {
	long long r;

	r = 1;
	
	while(r <= v)
		r *= b;
	
	return r;
}