#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/prime.h"
#include "IamLupo/number.h"

using namespace std;

/*
	Find the lowest sum for a set of five primes for which any
	two primes concatenate to produce another prime.
*/

static IamLupo::Primes primes;

bool bruteforce(vector<int> &v, int* m, int sum, int index, int max) {
	int i;
	vector<int> t;
	
	if(v.size() == max) {
		//Calculate the new max value
		*m = sum;
		
		//Debug
		//for(i = 0; i < v.size(); i++)
		//	cout << v[i] << endl;
		
		return true;
	}
	
	/*
		rules:
			the prime index can never be out of range
			if there is no known max value we will run this
			if sum + next prime is still lower then the max value
	*/
	while(index < primes.size() && (*m == -1 || *m < sum + primes[index])) {
		/*
			check if index prime will be fit with the already found primes list
		*/
		if(IamLupo::Prime::isConcatenate(primes, v, primes[index])) {
			//Copy already valid primes
			t = v;
			
			//Push the new prime in the list
			t.push_back(primes[index]);
			
			//Start a new generation
			if(bruteforce(t, m, sum + primes[index], index + 1, max))
				return true;
		}
		
		index++;
	}
	
	return false;
}

int sumConcatenatePrimes(int l) {
	int m;
	vector<int> r;
	
	m = -1; //Unknown minimal sum
	
	bruteforce(r, &m, 0, 0, l);
	
	return m;
}

IamLupo::Primes f() {
	int i, j, s, p;
	string v;
	long long a, b;
	IamLupo::Primes l;
	
	for(i = 0; i < primes.size(); i++) {
		v = to_string(primes[i]);
		s = v.size();
		
		for(j = 0; j < s - 1; j++) {
			p = j + 1;
			a = IamLupo::Number::to(v.substr(0, p));
			b = IamLupo::Number::to(v.substr(p, s - p));
			
			if(IamLupo::Prime::is(primes, a) && IamLupo::Prime::is(primes, b)) {
				if(find(l.begin(), l.end(), a) == l.end())
					l.push_back(a);
				
				if(find(l.begin(), l.end(), b) == l.end())
					l.push_back(b);
			}
		}
	}
	
	return l;
}

int main() {
	primes = IamLupo::Prime::generate(8400);
	
	cout << "result = " << sumConcatenatePrimes(5) << endl;
	
	return 0;
}