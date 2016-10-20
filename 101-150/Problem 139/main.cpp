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
	Given that the perimeter of the right triangle is less than one-hundred million,
	how many Pythagorean triangles would allow such a tiling to take place?
*/

/*
	Generate Pythagorean triangles:
		m > n > 0
		
		a = m^2 - n^2
		b = 2mn
		c = m^2 + n^2
	
	Pythagorean triangles perimeter:
		a + b + c = 2m(m + n)
	
	Conclusion A:
		if we know that (3, 4, 5) is a valid triangle. Then we also know
		(6, 8, 10) and (9, 12, 15) are also a valid solution. The triangles are multiplied.
		The total triangles there are can be calculated by:
			max = max permimeter			
			total = max / 2m(m + n)
			
	Conclusion B:
		Data:
			n		m
			1       2
			2       5
			5       12
			12      29
			29      70
			70      169
			169     408
			408     985
			985     2378
			2378    5741
		
		These are the m and n that we are intrested in. We can spot a pattern in it.
		We see that m is the same as the next level n. Also the distance
		between n and m is the same as the total of m and n of the level before.
		
		The n^k and the m^k is the k position in my data
		
		n^0 = 1
		m^0 = 2
		
		Next level:
			n^k = m^(k-1)
			m^k = m^(k-1) + m^(k-1) + n^(k-1)
*/

/*
	Test all Pythagorean triangles
*/
int f_bruteforce(int l) {
	int m, n, r;
	long long x, y;
	
	//Init
	r = 0;
	
	for(n = 1; 2 * (n + 1) * ((n + 1) + n) < l; n++) {
		for(m = n + 1; 2 * m * (m + n) < l; m++) {
			//Pythagorean triangle
			x = pow(m, 2) - pow(n, 2);
			y = 2 * m * n;
			
			// When distance between x and y is 1
			if(x - y == 1 || y - x == 1) {
				r += l / (2 * m * (m + n));
				
				//Debug
				cout << n << "	" << m << "	" << endl;
			}
		}
	}
	
	return r;
}

/*
	Generates the right n and m values for solution
*/
int f(int l) {
	int t, m, n, r;
	
	//Init
	m = 2;
	n = 1;
	r = 0;
	
	while(2 * m * (m + n) < l) {
		r += l / (2 * m * (m + n));
		
		t = n;
		n = m;
		m = m + m + t;
	}
	
	return r;
}

int main() {
	cout << "Result = " << f(100000000) << endl;
	
	return 0;
}
