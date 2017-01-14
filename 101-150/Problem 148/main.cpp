#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>

#include "gmp.h"
#include "IamLupo/math.h"
#include "IamLupo/triangular.h"

using namespace std;

/*
	Find the number of entries which are not divisible by 7 in the first
	one billion (10^9) rows of Pascal's triangle.
*/

/*
	Data:
		1,	2,	3,	4,	5,	6,	7,
		2,	4,	6,	8,	10,	12,	14,
		3,	6,	9,	12,	15,	18,	21,
		4,	8,	12,	16,	20,	24,	28,
		5,	10,	15,	20,	25,	30,	35,
		6,	12,	18,	24,	30,	36,	42,
		7,	14,	21,	28,	35,	42,	49,
		2,	4,	6,	8,	10,	12,	14,
		4,	8,	12,	16,	20,	24,	28,
		
	Conclusion A:
		In the data we can look clearly for a pattern.
		We have a set {1,	2,	3,	4,	5,	6,	7}.
		First row its multipiplied by 1, second row by 2, third by 3,....
	
	Conclusion B:
		After 7e row the set will be updated + its own value.
		
		Set 1: {1,	2,	3,	4,	5,	6,	7}
		Set 2: {2,	4,	6,	8,	10,	12,	14}
		Set 3: {3,	6,	9,	12,	15,	18,	21}
		Set 4: {4,	8,	12,	16,	20,	24,	28}
		Set 5: {5,	10,	15,	20,	25,	30,	35}
		Set 6: {6,	12,	18,	24,	30,	36,	41}
		Set 7: {7,	14,	21,	28,	35,	42,	48}
		
	Conclusion C:
		If you have a number "n" every time the number can be divided by 7 there
		is a extra layer that stores a set {1,	2,	3,	4,	5,	6,	7} as a start.
		the first layer increased by the add function and pass its sets to
		the next layer. Every layer can only loop 7 times and then it
		will return to the parent layer.
*/

typedef vector<unsigned long long> Set;

Set add(const Set &a, const Set &b) {
	int i;
	Set r;
	
	//Init
	r = a;
	
	for(i = 0; i < r.size(); i++)
		r[i] += b[i];
	
	return r;
}

long long calc(long long *n, const Set &s, int m) {
	int i;
	Set s_next;
	long long r;
	
	//Init
	r = 0;
	s_next = s;
	
	if(m > 1) {
		for(i = 0; i < 7 && *n != 0; i++) {
			r += calc(n, s_next, m - 1);
			
			//Update
			s_next = add(s_next, s);
		}
	} else {
		if(*n >= 49) {
			for(i = 0; i < s_next.size(); i++)
				r += s_next[i] * IamLupo::Triangular::get(7);
		
			*n -= 49;
		} else {
			for(i = 0; i < s_next.size(); i++)
				if(*n % 7 >= i + 1)
					r += s_next[i] * IamLupo::Triangular::get((*n / 7) + 1);
				else
					r += s_next[i] * IamLupo::Triangular::get(*n / 7);
			
			*n = 0;
		}
	}
	
	return r;
}

long long f(int p) {
	int i, m;
	long long n, r;
	Set s;
	
	//Init
	r = 0;
	m = 0;
	n = pow(10, p);
	s = {1, 2, 3, 4, 5, 6, 7};
	
	while(n / 7 > 1) {
		n /= 7;
		m++;
	}
	
	n = pow(10, p);
	
	r += calc(&n, s, m);
	
	return r;
}

int main() {
	// Example: 2361 of the 5050 entries are not divisible by 7
	//cout << "Result = " << f(2) << endl;
	
	cout << "Result = " << f(9) << endl;
	
	return 0;
}
