#include "IamLupo/pentagonal.h"

/*
	https://en.wikipedia.org/wiki/Pentagonal_number
*/
long long IamLupo::Pentagonal::get(long long n) {
	return (3 * n * n - n) / 2;
}

IamLupo::Pentagonals IamLupo::Pentagonal::generate(int l) {
	int i;
	IamLupo::Pentagonals r;
	
	for(i = 1; i <= l; i++)
		r.push_back(IamLupo::Pentagonal::get(i));
	
	return r;
}