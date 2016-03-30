#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"

using namespace std;

/*
	How many n-digit positive integers exist which are also an nth power?
*/

int countNthPower() {
	int i, j, c;
	mpz_t v;
	string s;
	
	//Init
	mpz_init(v);
	i = 1;
	j = 1;
	c = 0;
	
	while(j < 30) {
		// v = i^j
		mpz_ui_pow_ui(v, i, j);
		
		//Convert
		s = mpz_get_str(NULL, 10, v);
		
		if(s.size() == j) {
			c++;
			i++;
		}
		else if(s.size() > j) {
			j++;
			i = 1;
		}
		else
			i++;
	}
	
	return c;
}

int main() {
	cout << "result = " << countNthPower() << endl;
	
	return 0;
}