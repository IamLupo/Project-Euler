#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/string.h"

using namespace std;

/*
	Find the largest palindrome made from the product of two 3-digit numbers.
*/

int maxPalindromic(int l) {
	int i, j, v, r, m;
	string s;
	
	r = 0;
	m = pow(10, l) - 1;
	
	for(i = m; i > 0; i--) {
		for(j = m; j > i; j--) {
			v = i * j;
			s = std::to_string(v);
			
			if(IamLupo::String::isPalindrome(s) && r < v)
				r = v;
		}
	}
	
	return r;
}


int main() {
	cout << "result = " << maxPalindromic(3) << endl;
	
	return 0;
}
