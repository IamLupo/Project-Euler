#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "gmp.h"

#include "IamLupo/math.h"

using namespace std;

/*
	How many ways are there to write the number 1/2 as a sum of inverse squares
	using distinct integers between 2 and 80 inclusive?
*/

typedef vector<long long> Squars;
typedef vector<long long> InverseSquars;

// Static variables
static InverseSquars invSquares;
static InverseSquars invSquaresLeftOver;
static long long LCM;

/*
	Generate square demoninators that are relevant.
*/
Squars get(int l) {
	int i, j, v;
	Squars s;
	vector<long long> known, primes;
	
	//Init
	primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
	
	
	for(i = 2; i <= l; i++) {
		v = i;
		for(j = 0; j < primes.size() && primes[j] * primes[j] <= l; j++)
			while(v % primes[j] == 0)
				v /= primes[j];
		
		if(v == 1 || v == 7 || v == 13)
			s.push_back(i * i);
	}
	
	return s;
}

/*
	Generate inverse Square results based with the LCM
*/
InverseSquars get(Squars &s) {
	int i;
	InverseSquars is;
	
	for(i = 0; i < s.size(); i++)
		is.push_back(LCM / s[i]);
	
	return is;
}

/*
	Least Common Multiple
	
	Reference:
		https://www.calculatorsoup.com/calculators/math/lcm.php
*/
long long calc_LCM(Squars &s) {
	int i;
	long long r;

	// Init
	r = s[0];
	
    for(i = 1; i < s.size(); i++)
        r = (s[i] * r) / (IamLupo::Math::gcd(s[i], r));
	
    return r;
}

/*
	Generates a list of fraction numerator to check it still
	has enough fracitons left to generate the target
*/
InverseSquars getLeftOver(InverseSquars &is) {
	int i;
	InverseSquars lo;
	
	// Init
	lo = is;
	
	for(i = lo.size() - 2; i >= 0; i--)
		lo[i] += lo[i + 1];
	
	return lo;
}

/*
	Finds total solutions to make the target "v"
*/
int find(long long v, int index) {
	int i, r;
	long long v2;
	
	//Init
	r = 0;
	
	for(i = index; i < invSquares.size(); i++) {
		v2 = v - invSquares[i];
		
		if(v2 == 0) {
			r++;
		} else if(v2 > 0 && v2 - invSquaresLeftOver[i] <= 0) {
			r += find(v2, i + 1);
		}
	}
	
	return r;
}

/*
	Finds total solutions to make the target "v"
	For debugging perpose it also shows all fractions that makes the target
*/
int find(long long v, int index, const vector<long long> &factors) {
	int i, j, r;
	long long v2;
	vector<long long> factors2;
	
	//Init
	r = 0;
	
	for(i = index; i < invSquares.size(); i++) {
		factors2 = factors;
		
		v2 = v - invSquares[i];
		factors2.push_back(invSquares[i]);
		
		if(v2 == 0) {
			// Debug
			for(j = 0; j < factors2.size(); j++) {
				if(j != 0)
					cout << " + ";
				
				cout << "1/" << LCM / factors2[j];
			}
			cout << " = 1/2" << endl;
			
			r++;
		} else if(v2 > 0 && v2 - invSquaresLeftOver[i] <= 0) {
			r += find(v2, i + 1, factors2);
		}
	}
	
	return r;
}

int f(int l) {
	long long lcm;
	Squars s;
	
	//Init
	s = get(l);
	LCM = calc_LCM(s);
	invSquares = get(s);
	invSquaresLeftOver = getLeftOver(invSquares);
	
	//return find(LCM / 2, 0);
	return find(LCM / 2, 0, {}); // Debug
}

int main() {
	//cout << "Result = " << f(35) << endl;
	//cout << "Result = " << f(45) << endl;
	cout << "Result = " << f(80) << endl;
	
	return 0;
}