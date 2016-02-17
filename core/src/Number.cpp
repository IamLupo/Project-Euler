#include <math.h>

#include "IamLupo/number.h"

long long IamLupo::Number::to(const std::vector<int> &v) {
	int i;
	long long r;
	
	r = 0;
	
	for(i = 0; i < v.size(); i++)
		r += v[i] * pow(10, i);
	
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