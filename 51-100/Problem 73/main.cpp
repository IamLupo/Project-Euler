#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>
 
using namespace std;
 
/*
	How many fractions lie between 1/3 and 1/2 in the sorted set of
	reduced proper fractions for d = 12,000?
*/
 
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
 
long long countProperFractions(int l) {
	int i, j;
	long long r;
	vector<int> mu(l + 1, 0);
	
	//Init
	r = 0;
	mu[1] = 1;
	
	for(i = 1; i <= l; i++) {
		//Generate Mobius
		for(j = 2 * i; j <= l; j += i)
			mu[j] -= mu[i];
		
		//Calculate Mobius inverse values
		if(i >= 2)
			for(j = 2; i * j <= l; j++)
				r += mu[i] * A103221(j);
		
		if(i >= 4)
			r += mu[1] * A103221(i);
	}
		
	return r;
}
 
int main() {
	cout << "result = " << countProperFractions(12000) << endl;
	
	return 0;
}