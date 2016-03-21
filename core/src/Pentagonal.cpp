#include "IamLupo/pentagonal.h"

/*
	https://en.wikipedia.org/wiki/Pentagonal_number
*/
bool IamLupo::Pentagonal::is(long long n) {
	int i, x, t;
	
	t = 1;
	x = 1;
	
	while(t < n) {
		x += 3;
		t += x;
	}
	
	if(n == t)	
		return true;
	
	return false;
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
		r.insert(v);
		x += 3;
		v += x;
	}
	
	return r;
}