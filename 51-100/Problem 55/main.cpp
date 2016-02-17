#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

#include "gmp.h"
#include "IamLupo/string.h"

using namespace std;

/*
	How many Lychrel numbers are there below ten-thousand?
*/

int countLychrelNumbers(int l, int it) {
	int i, j, c;
	string s;
	vector<string> v, t;
	mpz_t a, b;
	char buffer[10000];
	
	//Init
	c = 0;
	mpz_init(a);
	mpz_init(b);
	
	//Add all values in list
	for(i = 1; i <= l; i++)
		v.push_back(to_string(i));
	
	//Update list and remove values that are Palindrome
	for(i = 0; i < it; i++) {
		t.clear();
		for(j = 0; j < v.size(); j++) {
			//Reverse text
			s = string(v[j].rbegin(), v[j].rend());
			
			//Set 
			mpz_set_str(a, v[j].c_str(), 10);
			mpz_set_str(b, s.c_str(), 10);
			
			// a + b
			mpz_add(a, a, b);
			
			//Save result
			mpz_get_str(buffer, 10, a);
			v[j] = buffer;
			
			//Check if Palindrome
			if(!IamLupo::String::isPalindrome(v[j]))
				t.push_back(v[j]);
		}
		v = t;
	}
	
	return v.size();
}

int main() {
	cout << "result = " << countLychrelNumbers(10000, 25) << endl;
	
	return 0;
}