#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	How many ways can a row measuring fifty units in length be filled?
*/

/* Slow Recursive */
static int MINIMUM = 3;

long long count(int v, int len) {
	int i, j;
	long long r;
	
	//Init
	r = 1;
	
	for(i = 1; v + i <= len; i++)
		r++;
	
	for(i = 1; i <= len - v; i++)
		for(j = MINIMUM; j <= len - v - i; j++)
			r += count(j, len - v - i);
	
	return r;
}

long long f2(int len) {
	int i;
	long long r;
	
	//Init
	r = 1;
	
	for(i = MINIMUM; i <= len; i++)
		r += count(i, len);
	
	return r;
}

/* Fast Solution */
long long binomial_coefficient(unsigned long n, unsigned long k) {
    unsigned long i;
    long long b;
	
    if (0 == k || n == k)
        return 1;
    
    if (k > n)
        return 0;
    
    if (k > (n - k))
        k = n - k;
    
    if (1 == k)
        return n;
    
    b = 1;
    for (i = 1; i <= k; ++i) {
        b *= (n - (k - i));
		
        if (b < 0)
			return -1; /* Overflow */
        
		b /= i;
    }
	
    return b;
}

long long f(int n) {
	int k;
	long long r;
	
	//Init
	r = 0;
	n++;
	
	for(k = 0; k <= n / 4; k++)
		r += binomial_coefficient(n - (2 * k), 2 * k);
	
	return r;
}

int main() {
	cout << "Result = " << f(50) << endl;
	
	return 0;
}
