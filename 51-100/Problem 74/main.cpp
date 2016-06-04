#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <set>

#include "IamLupo/number.h"
#include "IamLupo/vector.h"

using namespace std;

/*
	How many chains, with a starting number below one million,
	contain exactly sixty non-repeating terms?
*/

static vector<int> factorial = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };

/*
	Example:
		f(145) = 1! + 4! + 5! = 1 + 24 + 120 = 145
*/
long long algorithem(long long n) {
	int i;
	long long r;
	vector<int> v;
	
	r = 0;
	v = IamLupo::Vector::to(n);
	
	for(i = 0; i < v.size(); i++)
		r += factorial[v[i]];
	
	return r;
}

int run(int v, int max = 60) {
	int i, r;
	set<int> l;
	
	//Init
	r = v;
	l.insert(r);
	
	for(i = 1; i <= max; i++) {
		r = algorithem(r);
		
		if(r == v || l.find(r) != l.end())
			return l.size();
		
		l.insert(r);
	}
	
	return -1; // More then max
}

/*
	Example:
		f({1}) = 1 = 1 possebility
		f({1,9}) = 19 and 91 = 2 possebilities
		f(1,4,4) = 144, 414 and 441 = 3 possebilities
		f(1,4,3) = 143, 134, 341, 314, 413, 431 = 6 possebilities
*/
int count(const vector<int> &v) {
	int r;
	vector<int> l = v;
	
	//Init
	r = 0;
	
	do {
		if(l[l.size() - 1] != 0)
			r++;
		
	} while(next_permutation(l.begin(), l.end()));
	
	return r;
}

/*
	Numbers with digits in nondecreasing order.
	
	http://oeis.org/A009994
*/
bool next(vector<int> &v, int max = 6) {
	int i, p;
	
	//Init
	p = 0;
	
	//increase first value;
	v[p]++;
	
	//Check for overflow
	while(v[p] == 10) {
		//Next position
		p++;
		
		//Check if position reached size array
		if(p == v.size()) {
			//Did we reached the max size?
			if(p == max)
				return false; //There is no next value to give
			else { //Add a extra value and initialize the state
				for(i = 0; i < v.size(); i++)
					v[i] = 0;
				
				v.push_back(1);
				
				return true;
			}
		}
		
		//Increase next value
		v[p]++;
		
		//Update values before
		for(i = 0; i < p; i++)
			v[i] = v[p];
	}
	
	return true;
}

int f(int rt) {
	int r;
	vector<int> v, t;
	
	//Init
	r = 0;
	v = {0};
	
	while(next(v)) {
		if(run(IamLupo::Number::to(v)) == rt) {
			t = v;
			
			reverse(t.begin(), t.end());
			r += count(t);
			
			//Replace 1 to 0 and look for all possebilities
			if(t[0] == 1) {				
				t[0] = 0;
				r += count(t);
			}
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << f(60) << endl;
	
	return 0;
}