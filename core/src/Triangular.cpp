#include "IamLupo/triangular.h"

/*
	https://en.wikipedia.org/wiki/1_%2B_2_%2B_3_%2B_4_%2B_%E2%8B%AF
*/

bool IamLupo::Triangular::is(long long n) {
	int t, x;
	
	x = 1;
	t = 1;
	
	while(t < n) {
		x += 1;
		t += x;
	}
	
	if(t == n)
		return true;
	
	return false;
}

long long IamLupo::Triangular::get(long long n) {
	return (n * (n + 1)) / 2;
}

IamLupo::Triangulars IamLupo::Triangular::generate(int l) {
	int i, v, x;
	IamLupo::Triangulars r;
	
	v = 1;
	x = 1;
	
	while(v <= l) {
		r.push_back(v);
		x += 3;
		v += x;
	}
	
	return r;
}