#include "prime.h"
#include "number.h"

bool IamLupo::Prime::isPrime(const Primes &p, long long v) {
	int i;
	
	for(i = 0; i < p.size() && p[i] < v / 2; i++)
		if(v % p[i] == 0)
			return false;
	
	return true;
}

void IamLupo::Prime::generate(Primes &p, int l) {
	int i, j;
	std::vector<long long> a, b;
	
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
	
	p = a;
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
		if(!IamLupo::Prime::isPrime(p, (v * IamLupo::Number::nextBase(10, r[i])) + r[i]))
			return false;
		
		if(!IamLupo::Prime::isPrime(p, (r[i] * IamLupo::Number::nextBase(10, v)) + v))
			return false;
	}
	
	return true;
}