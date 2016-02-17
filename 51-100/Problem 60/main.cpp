#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>

#include "gmp.h"

#include "IamLupo/prime.h"
#include "IamLupo/number.h"

using namespace std;

/*
	Find the lowest sum for a set of five primes for which any
	two primes concatenate to produce another prime.
*/

static IamLupo::Primes primes;

void brutforce(vector<int> &r, int* m, int index, int max) {
	int s;
	vector<int> t;
	
	if(r.size() == max) {
		//Calculate the new max value
		*m = IamLupo::Number::sum(r);
		return;
	}
	
	//Calculate the sum of the valide values
	s = IamLupo::Number::sum(r);
	
	/*
		rules:
			the prime index can never be out of range
			if there is no known max value we will run this
			if s + next prime is still lower then the max value
	*/
	while(  (*m == -1 && primes[index] != 0) ||
			(*m < s + primes[index] && primes[index] != 0)) {
		
		/*
			check if index prime will be fit with the already found primes list
		*/
		if(IamLupo::Prime::isConcatenate(primes, r, primes[index])) {
			//Copy already valid primes
			t = r;
			
			//Push the new prime in the list
			t.push_back(primes[index]);
			
			//Start a new generation
			brutforce(t, m, index + 1, max);
		}
		
		index++;
	}
}

int sumConcatenatePrimes(int l) {
	int m;
	vector<int> r;
	
	m = -1; //Unknown minimal sum
	
	brutforce(r, &m, 0, l);
	
	return m;
}

int main() {
	IamLupo::Prime::generate(primes, 100);
	
	cout << "result = " << sumConcatenatePrimes(5) << endl;
	
	return 0;
}