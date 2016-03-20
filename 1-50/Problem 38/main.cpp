#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/vector.h"
#include "IamLupo/number.h"

using namespace std;

/*
	What is the largest 1 to 9 pandigital 9-digit number that can be formed
	as the concatenated product of an integer with (1,2, ... , n) where n > 1?
*/

static vector<int> pattern = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

int getLargestPandigitalProduct() {
	int i, n, t, r;
	vector<int> v, v2;
	bool f;
	
	//Init
	r = 0;
	
	//Test number
	for(i = 1; i < 10000; i++) {
		f = true;
		n = 1;
		v.clear();
		
		//Keep looping n till you have enough numbers
		while(f) {
			//Calculate next number
			t = i * n;
			
			//Convert number to a vector and add to the list
			v2 = IamLupo::Vector::to(t);
			v.insert(v.end(), v2.begin(), v2.end());
			
			//Check if the numbers we have collected is enough
			v2 = v;
			sort(v2.begin(), v2.end());
			if(IamLupo::Vector::same(v2, pattern)) {
				reverse(v.begin(), v.end());
				t = IamLupo::Number::to(v);
				
				//Check if we found a new higher number
				if(t > r)
					r = t;
			}
			
			/*
				Quit n loop if our collected numbers not match
				the pattern or has to much elements
			*/
			if(v.size() > pattern.size())
				f = false;
			
			n++;
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << getLargestPandigitalProduct() << endl;
	
	return 0;
}