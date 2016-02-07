#include "prime.h"

bool IamLupo::Prime::isPrime(long long v) {
	int i;
	
	for(i = 0; i < IamLupo::Prime::v.size() && IamLupo::Prime::v[i] < v / 2; i++)
		if(v % IamLupo::Prime::v[i] == 0)
			return false;
	
	return true;
}

void IamLupo::Prime::generate(int l) {
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
	
	IamLupo::Prime::v = a;
}
