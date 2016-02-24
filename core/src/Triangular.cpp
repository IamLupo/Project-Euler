#include "IamLupo/triangular.h"

/*
	https://en.wikipedia.org/wiki/1_%2B_2_%2B_3_%2B_4_%2B_%E2%8B%AF
*/
long long IamLupo::Triangular::get(long long n) {
	return (n * (n + 1)) / 2;
}

IamLupo::Triangulars IamLupo::Triangular::generate(int l) {
	int i;
	IamLupo::Triangulars r;
	
	for(i = 1; i <= l; i++)
		r.push_back(IamLupo::Triangular::get(i));
	
	return r;
}