#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

/*
	What is the largest 1 to 9 pandigital 9-digit number that can be formed
	as the concatenated product of an integer with (1,2, ... , n) where n > 1?
*/

static vector<int> pattern = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

/*
	-1	is not enough elements
	0	is same as the pattern
	1	is not the same as the pattern
*/
int cmpDigits(vector<int> &v) {
	int i;
	vector<int> v2;
	
	v2 = v;
	
	// Not enough elements
	if(v2.size() < pattern.size())
		return -1;
	
	// To much elements
	else if(v2.size() > pattern.size())
		return 1;
	
	// Check if it is same pattern
	sort(v2.begin(), v2.end());
	for(i = 0; i < pattern.size(); i++)
		if(pattern[i] != v2[i])
			return 1;
	
	return 0;
}

int getLargestPandigitalProduct(int r) {
	int i, j, n, t, c, l;
	vector<int> v, v2;
	bool f;
	
	//Init
	l = 0;
	
	//Test number
	for(i = 1; i < r; i++) {
		f = true;
		n = 1;
		v.clear();
		
		//Keep looping n till you have enough numbers
		while(f) {
			v2.clear();
			
			//Calculate next number
			t = i * n;
			
			//Split number into base 10 parts
			while(t != 0) {
				v2.insert(v2.begin(), 1, t % 10);
				t /= 10;
			}
			
			//fix: Numbers must be added to the end of the result
			for(j = 0; j < v2.size(); j++)
				v.push_back(v2[j]);
			
			//Check if the numbers we have collected is enough
			c = cmpDigits(v);
			if(c == 0) {
				t = 0;
				
				//generate the collected numbers back to a integer
				for(j = 0; j < v.size(); j++)
					t += v[j] * pow(10, v.size() - 1 - j);
				
				//Check if we found a new higher number
				if(t > l)
					l = t;
			}
			
			/*
				Quit n loop if our collected numbers not match
				the pattern or has to much elements
			*/
			if(c > -1)
				f = false;
			
			n++;
		}
	}
	
	return l;
}

int main() {
	cout << "result = " << getLargestPandigitalProduct(10000) << endl;
	
	return 0;
}