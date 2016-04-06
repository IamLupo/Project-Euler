#include "math.h"

#include "IamLupo/pentagonal.h"

/*
	https://en.wikipedia.org/wiki/Pentagonal_number
*/
bool IamLupo::Pentagonal::is(long long v) {
	double r;
	
	r = (sqrt(1 + 24 * v) + 1.0) / 6.0;
	
    return r == ((int)r);
}

long long IamLupo::Pentagonal::get(long long n) {
	return (3 * n * n - n) / 2;
}

IamLupo::Pentagonals IamLupo::Pentagonal::generate(int l) {
	int i, v, x;
	IamLupo::Pentagonals r;
	
	v = 1;
	x = 1;
	
	while(v <= l) {
		r.push_back(v);
		x += 3;
		v += x;
	}
	
	return r;
}