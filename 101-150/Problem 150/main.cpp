#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/triangular.h"

using namespace std;

/*
	Find the smallest possible sub-triangle sum.
*/

typedef vector<long long> Triangle;

#define MIN_FIND 	100

struct Position {
	int x;
	int y;
};

long long to_index(const Position &p) {	
	return IamLupo::Triangular::get(p.y - 1) + p.x - 1;
}

int depth(const Triangle &t) {
	int e, r;
	
	//Init 
	r = 1;
	e = 1;
	
	while(e < t.size()) {
		e += r;
		r++;
	}
	
	return r - 1;
}

Triangle gen_example() {
	Triangle r;
	
	r = {
		15,
		-14, -7,
		20, -13, -5,
		-3, 8, 23, -26,
		1, -4, -5, -18, 5,
		-16, 31, 2, 9, 28, 3
	};
	
	return r;
}

Triangle gen_pseudo_random() {
	int k;
	long long t, mod;
	Triangle r;
	
	//Init
	t = 0;
	mod = 1048576;
	
	for(k = 1; k <= 500500; k++) {
		t = (615949 * t + 797807) % mod;
		
		r.push_back(t - 524288);
	}
	
	return r;
}

long long check(const Triangle &t, const Position &p) {
	int x, y;
	long long v, r;
	
	//Init
	v = 0;
	r = 0;
	
	for(y = 1; p.y + y - 1 <= depth(t); y++) {
		for(x = 1; x <= y; x++)
			v += t[to_index({p.x + x - 1, p.y + y - 1})];
		
		if(r > v)
			r = v;
	}
	
	return r;
}

long long f(const Triangle &t) {
	int x, y, c;
	long long v, r;
	
	//Init
	r = 0;
	c = 0;
	
	for(y = 1; y <= depth(t) - 1; y++)
		for(x = 1; x <= y; x++) {
			v = check(t, {x, y});
			c++;
			
			if(r > v) {
				r = v;
				c = 0;
			}
			
			if(MIN_FIND <= c)
				return r;
		}
	
	return r;
}

int main() {
	//Triangle t = gen_example();
	Triangle t = gen_pseudo_random();
	
	cout << "Result = " << f(t) << endl;
	
	return 0;
}
