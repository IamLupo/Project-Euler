#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdint.h>

/*
	sum of the proper divisors:
	28	>	1 + 2 + 4 + 7 + 14 = 28
	
	abundant number:
	12	>	1 + 2 + 3 + 4 + 6 = 16
	
	Find the sum of all the positive integers which cannot be written
	as the sum of two abundant numbers.
*/

using namespace std;

bool isAbundantNumber(int nr) {
	int sum, i;
	
	sum = 1;
	
	for(i = 2; i <= (nr / 2); i++) {
		if(nr % i == 0) {
			sum += i;
		}
	}
	
	return (sum > nr);
}

bool addListToValue(vector<int>& list, int value) {
	int i, j;
	
	for(i = 0; i < list.size(); i++) {
		if(list[i] > value)
			return false;
		
		for(j = 0; j < list.size(); j++) {
			if(list[i] + list[j] == value)
				return true;
			
			if(list[i] + list[j] > value)
				j = list.size();
		}
	}
	
	return false;
}

uint64_t sumNoneAbundantNumbers() {
	int i;
	uint64_t sum;
	vector<int> list;
	
	//Init
	sum = 0;
	
	// Get All Abundant Numbers
	for(i = 12; i <= 28123; i++) {
		if(isAbundantNumber(i))
			list.push_back(i);
	}
	
	//Find None Abundant Numbers
	for(i = 1; i <= 28123; i++) {
		if(!addListToValue(list, i))
			sum += i;
	}
	
	return sum;
}

int main() {
	cout << sumNoneAbundantNumbers() << endl;

	return 0;
}