#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>

#include "IamLupo/prime.h"

using namespace std;

/*
	Find the sum of the first forty prime factors of R(10^9).
*/

/*
	Formula:
		R(k) = repunit of length k
		A(n) = shortes k in R(k) where R(k) can be divided by n (See Problem 130)
	
	Data:
		R(2) = 11
		R(3) = 3 * 37
		R(4) = 11 * 101
		R(5) = 41 * 271
		R(6) = 3 * 7 * 11 * 13 * 37
		R(7) = 239 * 4649
		R(8) = 11 * 73 * 101 * 137
		R(9) = 3 * 3 * 37 * 333667
		R(10) = 11 * 41 * 271 * 9091
		R(11) = 21649 * 513239
		R(12) = 3 * 7 * 11 * 13 * 37 * 101 * 9901
		R(13) = 53 * 79 * 265371653
		R(14) = 11 * 239 * 4649 * 909091
		R(15) = 3 * 31 * 37 * 41 * 271 * 2906161
		R(16) = 11 * 17 * 73 * 101 * 137 * 5882353
		R(17) = 2071723 * 5363222357
		R(18) = 3 * 3 * 7 * 11 * 13 * 19 * 37 * 52579 * 333667
		R(19) = 1111111111111111111
		R(20) = 11 * 41 * 101 * 271 * 3541 * 9091 * 27961
		
		R(10^2) = 11 * 41 * 101 * 251 * 271 * 3541 * 5051 * 9091 * 21401 * 25601 * 27961
				  * 60101 * 7019801 * 182521213001 * 14103673319201 * 78875943472201
				  * 1680588011350901
		R(10^3) = 11 * 41 * 73 * 101 * 137 * 251 * 271 * 401 * 751 * 1201 * 1601 * 3541
		          * 4001 * 5051 * 9091 * 21001 * 21401 * 24001 * 25601 * 27961 * 60101
				  * 76001 * 162251 * 1378001 * 1610501 * 1676321 * 7019801
				  
	Conclusion A:
		R(2) = 11
		
		for ever R(k) where k can be divided by 2 it use the prime multiplier 11
		
		This means R(10^9) has 11 in the answer
		
		Prove:
			R(4) = 11 * 101
			R(6) = 3 * 7 * 11 * 13 * 37
			R(8) = 11 * 73 * 101 * 137
			R(10) = 11 * 41 * 271 * 9091
			
	Conclusion B:
		A(41) = 5
		
		This means all R(k) where k can be divided by 5 has 41 in them
		
		Prove:
			R(10) = 11 * 41 * 271 * 9091
			R(15) = 3 * 31 * 37 * 41 * 271 * 2906161
			R(20) = 11 * 41 * 101 * 271 * 3541 * 9091 * 27961
			
		We need to check all prime numbers in the A function and
		check if the answer can be divived by 10^9
*/

static IamLupo::Primes primes;

int A(int n) {
	int k, c;
	
	//Init
	k = 1;
	c = 1;
	
	//Generate k
	while(c % n != 0) {
		c %= n;
		c *= 10;
		c += 1;
		k++;
	}
	
	return k;
}

long long f(int p, int l) {
	int i;
	long long n;
	set<int> r;
	
	//Init
	n = pow(10, p);
	
	for(i = 1; i < primes.size(); i++) {
		if(i != 2 && n % A(primes[i]) == 0) {
			//Debug
			cout << primes[i] << endl;
			
			//Save result
			r.insert(primes[i]);
			
			//Check limit
			if(r.size() == l)
				return accumulate(r.begin(), r.end(), 0);
		}
	}
	
	return accumulate(r.begin(), r.end(), 0);
}

int main() {
	primes = IamLupo::Prime::generate(200000);

	cout << "Result = " << f(9, 40) << endl;

	return 0;
}
