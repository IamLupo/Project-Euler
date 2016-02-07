#include <math.h>

#include "number.h"

std::vector<int> IamLupo::Number::toVector(long long v) {
	std::vector<int> r;
	
	while(v != 0) {
		r.push_back(v % 10);
		v /= 10;
	}
	
	return r;
}

long long IamLupo::Number::toInteger(const std::vector<int> &v) {
	int i;
	long long r;
	
	r = 0;
	
	for(i = 0; i < v.size(); i++)
		r += v[i] * pow(10, i);
	
	return r;
}