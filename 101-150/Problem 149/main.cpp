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

using namespace std;

/*
	Find the greatest sum of (any number of) adjacent entries in any direction
*/

typedef vector<vector<long long>> Grid;

struct Position {
	int x;
	int y;
};

Position to_pos(int index) {
	Position r;
	
	r.x = (index - 1) % 2000;
	r.y = (index - 1) / 2000;
		
	return r;
}

Grid gen_example() {
	Grid r(4, vector<long long>(4, 0));
	
	r = {
		{	-2,	5,	3,	2	},
		{	9,	-6,	5,	1	},
		{	3,	2,	7,	3	},
		{	-1,	8,	-4,	8	},
	};
	
	return r;
}

Grid gen_lagged_fibonacci() {
	int k;
	long long v;
	mpz_t x, y;
	Position p, p2, p3;
	Grid r(2000, vector<long long>(2000, 0));
	
	//Init
	mpz_init(x);
	mpz_init(y);
	
	for(k = 1; k <= 55; k++) {
		//Generate Positions
		p = to_pos(k);
		
		//Generate value
		//v = 100003 - (200003 * k) + (300007 * pow(k, 3));
		mpz_set_si(x, 100003);
		
		mpz_set_ui(y, 200003);
		mpz_mul_ui(y, y, k);
		mpz_sub(x, x, y);
		
		mpz_ui_pow_ui(y, k, 3);
		mpz_mul_ui(y, y, 300007);
		mpz_add(x, x, y);
		
		mpz_mod_ui(x, x, 1000000);
		
		v = mpz_get_si(x) % 1000000 - 500000;
		
		//Save Result
		r[p.y][p.x] = v;
		
		//Debug
		//cout << "{" << p.y << ", " << p.x << "} = " << v << endl;
	}
	
	for(k = 56; k <= 4000000; k++) {
		//Generate Positions
		p = to_pos(k);
		p2 = to_pos(k - 24);
		p3 = to_pos(k - 55);
		
		//Generate value
		v = (r[p2.y][p2.x] + r[p3.y][p3.x] + 1000000) % 1000000 - 500000;
		
		//Save Result
		r[p.y][p.x] = v;
		
		//Debug
		//cout << "{"<< p.y << ", " << p.x << "} = " << round(v) << endl;
	}
	
	return r;
}

long long f(const Grid &g) {
	int i, j;
	long long ax, ay, bx, by, r;
	
	//Init
	r = 0;
	
	for(i = 0; i < g.size(); i++) {
		//Horizontal and Vertical
		ax = ay = bx = by = 0;
		
		for(j = 0; j < g.size(); j++) {
			ax += g[i][j];
			ay += g[j][i];
			bx += g[g.size() - 1 - i][g.size() - 1 - j];
			by += g[g.size() - 1 - j][g.size() - 1 - i];
			
			if(r < ax) r = ax;
			if(r < ay) r = ay;
			if(r < bx) r = bx;
			if(r < by) r = by;
		}
		
		//Diagonal
		ax = ay = bx = by = 0;
		
		for(j = 0; i + j < g.size(); j++) {
			ax += g[j][i + j];
			ay += g[j][g.size() - 1 - i - j];
			bx += g[i + j][j];
			by += g[g.size() - 1 - j][j + i];
			
			if(r < ax) r = ax;
			if(r < ay) r = ay;
			if(r < bx) r = bx;
			if(r < by) r = by;
		}
	}
	
	return r;
}

int main() {
	//Grid g = gen_example();
	Grid g = gen_lagged_fibonacci();
	
	//Check S10 = −393027 and S100 = 86613 
	Position p = to_pos(10);
	cout << g[p.y][p.x] << endl;
	
	p = to_pos(100);
	cout << g[p.y][p.x] << endl;
	
	cout << "Result = " << f(g) << endl;
	
	return 0;
}
