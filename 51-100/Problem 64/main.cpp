#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/sqrt.h"

using namespace std;

/*
	How many continued fractions for N ≤ 10000 have an odd period?
*/

/*
	        b			b(sqrt(c + d))    				    
	a, -----------  =  ---------------- =
	   sqrt(c - d)        c - d^2
	   
	x = c - d^2
	y = d / x
	
	a = y;
	b = x;
	d = (d - x * y) * -1
	
		sqrt(c - d)
	y, ---------------
			x
*/
vector<int> fraction_failed_attempt_1(int c) {
	int i, a, b, d, x, y;
	vector<int> r;

	//Calculate a
	a = 1;
	while(c / a >= a)
		a++;
	a--;
	
	//cout << a << endl;
	
	//Save Result
	r.push_back(a);
	
	d = a;
	b = 1;
	for(i = 0; i < 15 && c != pow(d, 2); i++) {
		x = (c - pow(d, 2)) / b;
		
		y = (2 * d) / x;
		
		if(y == 0)
			y++;
		
		d = (d - (x * y)) * -1;
		
		a = y;
		b = x;
	
		//Debug
		//cout << x << " " << y << " " << d << endl;
		
		//Save Result
		r.push_back(y);
	}
	
	return r;
}

/*
Generate e:
	a	b	c	d	e
	23	4	4	1	1
	23	1	3	7	3
	23	3	3	2	1
	23	1	4	7	8
	23	8	4	1	1
	23	1	3	7	3
	23	3	3	2	1
	23	1	4	7	8

	e = c^((c - b)/(b + b^a))
	e = sqrt(c^((c - b)/b^a))
	y = sqrt(c^((c - b)/b^a))

Generate new c:
	a	b	c	d	e	y
	23	4	4	1	1	3
	23	1	3	7	3	3
	23	3	3	2	1	4
	23	1	4	7	8	4
	23	8	4	1	1	3
	23	1	3	7	3	3
	23	3	3	2	1	4
	23	1	4	7	8	4

	y = c - (-e)^(-(a*c))
	
Generate new d:
	a	b	c	d	e	y
	23	4	4	1	1	7
	23	1	3	7	3	2
	23	3	3	2	1	7
	23	1	4	7	8	1
	23	8	4	1	1	7
	23	1	3	7	3	2
	23	3	3	2	1	7
	23	1	4	7	8	1

	y = (a - c^2)/d
*/
vector<int> fraction_failed_attempt_2(int a) {
	int i, b, c, d, e, t;
	vector<int> r;

	//Calculate b
	b = 1;
	while(a / b >= b)
		b++;
	b--;
	
	//Save Result
	r.push_back(b);
	
	c = b;
	d = 1;
	
	//Debug
	cout << a << "	" << b << "	" << c <<  "	" << d << endl;
	
	for(i = 0; i < 10; i++) {
		//e = sqrt(c^((c - b)/b^a))
		e = sqrt(pow(c, (c - b) / pow(b, a)));
		
		//Save c
		t = c;
		
		//Update
		//c = c - (-e)^(-(a*c))
		c -= pow((e * -1), (a * c) * -1);
		
		//d = (a - c^2) / d
		d = (a - pow(t, 2)) / d;
		b = e;
		
		//Debug
		cout << a << "	" << b << "	" << c <<  "	" << d << "	" << e << endl;
		
		//Save Result
		r.push_back(e);
	}
	
	return r;
}

/*
	https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Continued_fraction_expansion
*/
vector<int> fraction(int s) {
	int i, m, d, a0, a, x, y, z;
	vector<int> r;
	
	a0 = floor(sqrt(s));
	
	//if it has one generation
	if(a0 * a0 == s)
		return {a0};
	
	//Init
	m = 0;
	d = 1;
	a = a0;
	
	//Calculate first generation
	m = (d * a) - m;
	d = (s - (m * m)) / d;
	a = (a0 + m) / d;
	
	//Variables to check to stop loop
	x = m;
	y = d;
	z = a;
	
	//Save Result
	r.push_back(a0);
	r.push_back(a);
	
	for(i = 0; i < 1000000; i++) {
		//Calculate next generation
		m = (d * a) - m;
		d = (s - (m * m)) / d;
		a = (a0 + m) / d;
		
		//Check to stop at repetition
		if(x == m && y == d && z == a)
			return r;
		
		//Save Result
		r.push_back(a);
	}
	
	return r;
}

int countOddFractions(int l) {
	int i, c;
	IamLupo::Sqrt::CFraction fr;
	
	c = 0;
	
	for(i = 1; i <= l; i++) {
		fr = IamLupo::Sqrt::ContinuedFraction(i);
		
		if(fr.size() % 2 == 0)
			c++;
	}
	
	return c;
}

int main() {
	cout << "result = " << countOddFractions(10000) << endl;
	
	return 0;
}