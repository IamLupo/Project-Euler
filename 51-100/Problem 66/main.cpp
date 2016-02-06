#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdio.h>

#include "gmp.h"

using namespace std;

/*
	Find the value of D ≤ 1000 in minimal solutions of x for which
	the largest value of x is obtained.
*/

vector<string> getHenceSequence(const vector<int> &v, int l) {
	int i, vl, id, r;
	mpz_t x1, x2, y1, y2, t;
	
	//Init
	mpz_init_set_ui(x1, 1);
	mpz_init_set_ui(x2, v[0]);
	
	mpz_init_set_ui(y1, 0);
	mpz_init_set_ui(y2, 1);
	mpz_init(t);
	
	id = 0;
	vl = v.size() - 1;
	
	for(i = 1; i < l; i++) {
		//Generate x
		//t = x2
		mpz_set(t, x2);
		
		mpz_mul_ui(x2, x2, v[id + 1]);
		mpz_add(x2, x2, x1);
		
		//y1 = t
		mpz_set(x1, t);
		
		//Generate y
		//t = y2
		mpz_set(t, y2);
		
		//y2 = (y2 * v) + y1
		mpz_mul_ui(y2, y2, v[id + 1]);
		mpz_add(y2, y2, y1);
		
		//y1 = t
		mpz_set(y1, t);
		
		//Next id
		id = (id + 1) % vl;
	}
	
	return {mpz_get_str(nullptr, 10, x2), mpz_get_str(nullptr, 10, y2)};
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

int findLargest_failed_attempt(int l) {
	long i, y, d, h, t2;
	mpz_t v, t, x, h_x;
	vector<int> r, fr;
	vector<string> s;
	bool f;
	
	//Init
	h = 0;
	mpz_init(v);
	mpz_init(t);
	mpz_init(x);
	mpz_init_set_ui(h_x, 0);
	
	for(d = 1; d <= l; d++) {
		t2 = sqrt(d);
		if(t2 * t2 != d) {
			f = false;
			for(y = 1; !f && y <= 100000000; y++) {
				//v = d * y^2
				mpz_set_ui(v, y);
				mpz_pow_ui(v, v, 2);
				mpz_mul_ui(v, v, d);
				
				//t = sqrt(v)
				mpz_sqrt(t, v);
				
				//x = t + 1
				mpz_add_ui(t, t, 1);
				mpz_set(x, t);
				
				//t = (t * t) - 1
				mpz_mul(t, t, t);
				mpz_sub_ui(t, t, 1);				
				
				if(mpz_cmp(v, t) == 0) {
					if(mpz_cmp(h_x, x) < 0) {
						h = d;
						mpz_set(h_x, x);
					}
					//cout	<< mpz_get_str(nullptr, 10, x) << "	" << d << "	" << y << endl;
					
					fr = fraction(d);
					
					s = getHenceSequence(fr, 1);
					cout << s[0] << " " << s[1] << endl;
					
					
					s = getHenceSequence(fr, 2);
					cout << s[0] << " " << s[1] << endl;
					
					cout	<< mpz_get_str(nullptr, 10, x)
							<< "^2 - (" << d << " * " << y << "^2) = 1"<< endl;
					
					f = true;
				}
			}
		}
	}
	
	return h;
}

/*
	https://en.wikipedia.org/wiki/Pell's_equation
	http://www.ams.org/notices/200202/fea-lenstra.pdf
*/
int findLargest(int l) {
	int i, d, r, tt;
	mpz_t x, y, v, t, h;
	vector<int> fr;
	vector<string> s;
	bool f;
	
	//Init
	mpz_init(x);
	mpz_init(y);
	mpz_init(v);
	mpz_init(t);
	mpz_init_set_ui(h, 0);
	r = -1;
	
	for(d = 1; d <= l; d++) {
		tt = sqrt(d);
		if(tt * tt != d) {
			fr = fraction(d);
			f = false;
			
			for(i = 1; !f; i++) {
				s = getHenceSequence(fr, i);
				
				mpz_set_str(x, s[0].c_str(), 10);
				mpz_set_str(y, s[1].c_str(), 10);
				
				//x^2 - (d * y^2)
				mpz_mul(t, x, x);
				mpz_mul(v, y, y);
				mpz_mul_ui(v, v, d);
				mpz_sub(v, t, v);
				
				if(mpz_cmp_ui(v, 1) == 0) {
					f = true;
					
					if(mpz_cmp(h, x) < 0) {
						//h = x
						mpz_set(h, x);
						r = d;
					}
				}
			}
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << findLargest(1000) << endl;
	
	return 0;
}