#include "IamLupo/vector.h"

std::vector<int> IamLupo::Vector::to(long long v) {
	std::vector<int> r;
	
	while(v != 0) {
		r.push_back(v % 10);
		v /= 10;
	}
	
	return r;
}

bool IamLupo::Vector::same(std::vector<int> a, std::vector<int> b) {
	int i;
	
	if(a.size() != b.size())
		return false;
	
	for(i = 0; i < a.size(); i++) {
		if(a[i] != b[i])
			return false;
	}
	
	return true;
}