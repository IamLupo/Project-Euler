#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	How many fractions lie between 1/3 and 1/2 in the sorted set of
	reduced proper fractions for d ≤ 12,000?
*/

vector<vector<int>> dividers(int l) {
	int i, j;
	vector<vector<int>> r;
	
	//zero has no dividers
	r.push_back({0});
	
	//All the others have 1 as divider
	for(i = 1; i <= l; i++)
		r.push_back({1});
	
	//Find the other dividers
	for(i = 2; i <= l / 2; i++)
		for(j = 2; i * j <= l; j++)
			r[i * j].push_back(i);
	
	return r;
}

/*
	Data:
		1, -1, -1, 0, -1, 1, -1, 0, 0, 1, -1, 0, -1, 1, 1, 0, -1, 0,
		-1, 0, 1, 1, -1, 0, 0, 1, 0, 0, -1, -1, -1, 0, 1, 1, 1, 0, -1,
		1, 1, 0, -1, -1, -1, 0, 0, 1, -1, 0, 0, 0, 1, 0, -1, 0, 1, 0, 

	Property:
		μ(n) = 1 if n is a square-free positive integer with an even number of prime factors.
		μ(n) = −1 if n is a square-free positive integer with an odd number of prime factors.
		μ(n) = 0 if n has a squared prime factor.
	
	Reference:
		https://oeis.org/A008683
		https://en.wikipedia.org/wiki/M%C3%B6bius_function
*/
vector<int> Mobius(long long n) {
	int i, j;
	vector<int> r(n + 1, 0);
	
	r[1] = 1;

	for(i = 1; i <= n; i++)
		for(j = 2 * i; j <= n; j += i)
			r[j] -= r[i];
	
	return r;
}

/*
	Data:
		1, 0, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 3, 2, 3, 3, 3, 3, 4, 3, 4, 4,
		4, 4, 5, 4, 5, 5, 5, 5, 6, 5, 6, 6, 6, 6, 7, 6, 7, 7, 7, 7, 8, 7,
		8, 8, 8, 8, 9, 8, 9, 9, 9, 9, 10, 9, 10, 10, 10, 10,
	
	Formula:
		a(n) = floor(n/6)+1 unless n=1(mod6); if n=1(mod6), a(n) = floor(n/6)
	
		Bob Selcoe, Sep 27 2014
	
	Reference:
		https://oeis.org/A103221
*/
long long A103221(long long n) {
	if(n % 6 == 1)
		return n / 6;
	else
		return (n / 6) + 1;
}

/*
	Data:
		0,  1,  0,  0,  1,  0,  1,  1,  1,  0,  2,  1,  2,  1,  1,  1,  3,  1,
		3,  2,  2,  1,  4,  1,  3,  2,  3,  2,  5,  2,  5,  3,  3,  2,  4,  2,
		6,  3,  4   2,  7,  2,  7,  4,  4,  3,  8,  3,  7,  4,  5,  4,  9,  3,
		6,  4,  6,  4,  10, 2,  10, 5,  6,  5,  8,  4,  11, 6,  7,  4,  12, 4,
		12, 6,  7,  6,  10, 4,  13, 6,  9,  6,  14, 4,  10, 7,  9,  6,  15, 4,
		12, 8,  10, 7,  12, 5,  16, 7
	
	Formula:
		SUM_{d|n} mu(d) * A103221(n/d), where mu is Mobius function (A008683).
	
		Andrew Baxter, Jun 06 2008
	
	Reference:
		https://oeis.org/A128115
*/
long long A128115(long long n, vector<int> &mu, vector<int> &div) {
	int i;
	long long r;
	
	//Init
	r = 0;
	
	if(n == 3)
		return 0;
	
	for(i = 0; i < div.size(); i++)
		r += mu[div[i]] * A103221(n / div[i]);
	
	return r;
}

long long countProperFractions(int l) {
	long long r;
	vector<int> mu;
	vector<vector<int>> div;
	
	//Init
	r = 0;
	div = dividers(l);
	mu = Mobius(l);
	
	for(int i = 3; i <= l; i++)
		r += A128115(i, mu, div[i]);
	
	return r;
}

int main() {
	cout << "result = " << countProperFractions(12000) << endl;
	
	return 0;
}