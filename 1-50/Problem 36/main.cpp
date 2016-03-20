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
	Find the sum of all numbers, less than one million,
	which are palindromic in base 10 and base 2.
*/

int sumPalindromic(int m) {
	int i, r;
	string v;
	
	//Init
	r = 0;
	
	for(i = 1; i < m; i++) {
		if(IamLupo::String::isPalindrome(i)) {
			v = IamLupo::String::binairy(i);
			if(IamLupo::String::isPalindrome(v) && v[0] == '1') {
				r += i;
				
				//Debug
				//cout << i << " > " << v << endl;
			}
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << sumPalindromic(1000000) << endl;
		
	return 0;
}