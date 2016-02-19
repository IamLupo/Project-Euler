#include <algorithm>
#include <math.h>

#include "IamLupo/prime.h"
#include "IamLupo/number.h"

bool IamLupo::Prime::is(const IamLupo::Primes &p, long long v) {
	int i;
	std::vector<long long>::const_iterator it;
	
	if(v <= p.back()) {
		it = std::find(p.begin(), p.end(), v);
		
		if(it != p.end())
			return true;
	
		return false;
	} else {
		for(i = 0; i < p.size() && p[i] <= sqrt(v); i++)
			if(v % p[i] == 0)
				return false;
		
		return true;
	}
}

IamLupo::Primes IamLupo::Prime::generate(int l) {
	int i, j;
	IamLupo::Primes a, b;
	
	for(i = 2; i <= l * l; i++)
		a.push_back(i);
	
	for(i = 2; i <= l; i++) {
		for(j = 0; j < a.size(); j++) {
			if(a[j] % i != 0 || a[j] <= i)
				b.push_back(a[j]);
		}
		a = b;
		b.clear();
	}
	
	return a;
}

/*
	Example:
		f({3}, 5) = false, because 35 isnt prime
		f({3, 7}, 13) = false, because 133 and 713 isnt a prime
		f({3, 7}, 109) = true, because 3109, 1093, 1097 and 7109 are prime
*/
bool IamLupo::Prime::isConcatenate(const IamLupo::Primes &p, const std::vector<int> &r, int v) {
	int i;
	
	for(i = 0; i < r.size(); i++) {
		if(!IamLupo::Prime::is(p, (v * IamLupo::Number::nextBase(10, r[i])) + r[i]))
			return false;
		
		if(!IamLupo::Prime::is(p, (r[i] * IamLupo::Number::nextBase(10, v)) + v))
			return false;
	}
	
	return true;
}