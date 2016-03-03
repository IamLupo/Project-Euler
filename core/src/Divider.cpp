#include <algorithm>

#include "IamLupo/divider.h"

std::vector<int> IamLupo::Divider::get(long long v) {
	int i, d;
	std::vector<int> r;
	
	if(v == 4)
		return r;
	
	r.push_back(1);
	d = v / 2;
	
	for(i = 2; i < d; i++) {
		if(v % i == 0) {
			d = v / i;
			r.push_back(i);
			
			if(i != d)
				r.push_back(d);
		}
	}
	
	std::sort(r.begin(), r.end());
	
	return r;
}

long long IamLupo::Divider::sum(long long v) {
	int i, d;
	long long r;
	
	if(v == 4)
		return 3;
	
	r = 1;
	d = v / 2;
	
	for(i = 2; i < d; i++) {
		if(v % i == 0) {
			d = v / i;
			r += i;
			
			if(i != d)
				r += d;
		}
	}
	
	return r;
}

std::vector<int> IamLupo::Divider::generate_sum(long long l) {
	int i, j;
	std::vector<int> r;
	
	for(i = 0; i <= l; i++)
		r.push_back(0);
	
	for(i = 1; i <= l; i++) {
		for(j = i + i; j <= l; j += i) {
			r[j] += i;
		}
	}
	
	return r;
}