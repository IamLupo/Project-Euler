#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"

#include "IamLupo/prime.h"

using namespace std;

/*
	What is the least value of n for which the number of
	distinct solutions exceeds one-thousand?
*/

/*
	Data:
		n		n based on primes				x										solution	
		2		2^1								(2+1)									2
		4		2^2								(4+1)									3
		6		2^1 * 3^1						(2+1) * (2+1)							5
		12		2^2 * 3^1						(4+1) * (2+1)							8
		24		2^3 * 3^1						(6+1) * (2+1)							11
		30		2^1 * 3^1 * 5^1					(2+1) * (2+1) * (2+1)					14
		60		2^2 * 3^1 * 5^1					(4+1) * (2+1) * (2+1)					23
		120		2^3 * 3^1 * 5^1					(6+1) * (2+1) * (2+1)					32
		180		2^2 * 3^2 * 5^1					(4+1) * (4+1) * (2+1)					38
		210		2^1 * 3^1 * 5^1 * 7^1			(2+1) * (2+1) * (2+1) * (2+1)			41
		360		2^3 * 3^2 * 5^1					(6+1) * (4+1) * (2+1)					53
		420		2^2 * 3^1 * 5^1 * 7^1			(4+1) * (2+1) * (2+1) * (2+1)			68
		840		2^3 * 3^1 * 5^1 * 7^1			(6+1) * (2+1) * (2+1) * (2+1)			95
		1260	2^2 * 3^2 * 5^1 * 7^1			(4+1) * (4+1) * (2+1) * (2+1)			113
		1680	2^4 * 3^1 * 5^1 * 7^1			(8+1) * (2+1) * (2+1) * (2+1)			122
		2520	2^3 * 3^2 * 5^1 * 7^1			(6+1) * (4+1) * (2+1) * (2+1)			158
		4620	2^2 * 3^1 * 5^1 * 7^1 * 11^1	(2+1) * (2+1) * (2+1) * (2+1) * (2+1)	203

	Conclusion:
		x = v[1] * v[2] * v[3] ....
		v is odd
		
		solution = (x + 1) / 2
*/

static IamLupo::Primes primes;

void gen_value(const vector<int> &v, mpz_t output) {
	int i;
	
	//Init
	mpz_set_ui(output, 1);
	
	for(i = 0; i < v.size(); i++)
		mpz_mul_ui(output, output, pow(primes[i], v[i]));
}

int solution(const vector<int> &v) {
	int i, r;
	
	//Init
	r = 1;
	
	for(i = 0; i < v.size(); i++)
		r *= (v[i] * 2) + 1;
	
	return (r + 1) / 2;
}

static mpz_t g_val;

void algo(const vector<int> &v, int l) {
	int i;
	mpz_t x;
	vector<int> r;
	
	//Init
	mpz_init(x);
	
	for(i = 1; i <= v[v.size() - 1]; i++) {
		r = v;
		r.push_back(i);
		
		if(solution(r) >= l) {
			gen_value(r, x);
			
			if(mpz_cmp(g_val, x) > 0) {
				mpz_set(g_val, x);
				
				//Debug
				//cout << mpz_get_str(nullptr, 10, x) << endl;
			}
		} else {
			algo(r, l);
		}
	}
	
	mpz_clear(x);
}

string f(int l) {
	int i;
	string r;
	
	//Init
	mpz_init_set_ui(g_val, -1);
	
	for(i = 1; i <= 10; i++)
		algo({i}, l);
	
	r = mpz_get_str(nullptr, 10, g_val);
	
	mpz_clear(g_val);
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(300);
	
	cout << "Result = " << f(1000) << endl;
	
	return 0;
}
