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
	How many ways can a row measuring fifty units in length be tiled?
*/

/* Slow Recursive */
long long count(int v, int len) {
	int i, j;
	long long r;
	
	//Init
	r = 0;
	
	r += len - v + 1;
	
	for(i = 2; i <= 4; i++)
		for(j = 0; j <= len - v - i; j++)
			r += count(i, len - v - j);
	
	return r;
}

long long f(int n) {
	int i;
	long long r;
	
	//Init
	r = 1;
	
	for(i = 2; i <= 4; i++)
		r += count(i, n);
	
	return r; // Unknown
}

/* Fast way */
/*
	Tetranacci numbers
	
	a(n) = a(n-1) + a(n-2) + a(n-3) + a(n-4)
	
	Reference:
		https://en.wikipedia.org/wiki/Generalizations_of_Fibonacci_numbers#Tribonacci_numbers
		http://mathworld.wolfram.com/TetranacciNumber.html
		http://oeis.org/A000078
*/
long long A000078(int n) {
	int i;
	long long a, b, c, d, r;
	
	//Init
	a = 0;
	b = 0;
	c = 0;
	d = 1;
	
	for(i = 0; i < n; i++) {
		r = a + b + c + d;
		
		//Update
		a = b;
		b = c;
		c = d;
		d = r;
	}
	
	return r;
}

int main() {
	cout << "Result = " << A000078(50) << endl;
	
	return 0;
}
