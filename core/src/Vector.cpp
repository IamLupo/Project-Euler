#include <algorithm>

#include "IamLupo/vector.h"

std::vector<int> IamLupo::Vector::to(long long v) {
	std::vector<int> r;
	
	while(v != 0) {
		r.push_back(v % 10);
		v /= 10;
	}
	
	std::reverse(r.begin(), r.end());
	
	return r;
}

std::vector<long long> IamLupo::Vector::add(const std::vector<long long> &v) {
	int i;
	std::vector<long long> r;
	
	for(i = 0; i < v.size() - 1; i++)
		r.push_back(v[i] + v[i + 1]);
	
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

std::vector<std::vector<int>> IamLupo::Vector::mirror(std::vector<std::vector<int>> v) {
	int i, j;
	std::vector<int> t;
	std::vector<std::vector<int>> r;
	
	for(i = v.size(); i > 0; i--) {
		t = v[i - 1];
		std::reverse(t.begin(), t.end());
		r.push_back(t);
	}
	
	return r;
}