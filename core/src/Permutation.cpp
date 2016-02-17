#include <algorithm>

#include "IamLupo/permutation.h"

bool IamLupo::Permutation::is(long long a, long long b) {
	std::vector<int> x, y;
	
	x = IamLupo::Vector::to(a);
	y = IamLupo::Vector::to(b);
	
	std::sort(x.begin(), x.end());
	std::sort(y.begin(), y.end());
	
	if(IamLupo::Vector::same(x, y))
		return true;
	
	return false;
}

bool IamLupo::Permutation::is(const std::vector<int> &a, const std::vector<int> &b) {
	std::vector<int> x, y;
	
	x = a;
	y = b;
	
	std::sort(x.begin(), x.end());
	std::sort(y.begin(), y.end());
	
	if(IamLupo::Vector::same(x, y))
		return true;
	
	return false;
}