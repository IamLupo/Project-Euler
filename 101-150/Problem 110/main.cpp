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
	Find the maximum saving which can be achieved by removing redundant edges
	whilst ensuring that the network remains connected.
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

typedef vector<int> Powers;

static IamLupo::Primes primes;

/*
	Generate the value with the prime powers.
	
	Example:
		f({2, 1, 1, 1}) = 2^2 * 3^1 * 5^1 * 7^1 = 210
*/
void gen_n(const Powers &p, mpz_t output) {
	int i;
	mpz_t t;
	
	//Init
	mpz_init(t);
	mpz_set_ui(output, 1);
	
	for(i = 0; i < p.size(); i++) {
		// output *= prime[i] ^ p[i]
		mpz_set_ui(t, primes[i]);
		mpz_pow_ui(t, t, p[i]);
		mpz_mul(output, output, t);
	}
	
	//Clear
	mpz_clear(t);
}

static mpz_t bruteforce_n;
static long long bruteforce_l;

/*
	Bruteforce prime powers until minimum solutions in n found
*/
void bruteforce(const Powers &p, long long x) {
	int i, s, ch;
	long long x2;
	mpz_t n;
	Powers p2;
	
	//Init
	mpz_init(n);
	s = p.size();
	ch = (s == 0) ? 7 : p[s - 1];	//Max loops
	
	for(i = 1; i <= ch; i++) {
		//Generate next prime power level
		p2 = p;
		p2.push_back(i);
		
		//Update x
		x2 = x * ((i * 2) + 1);
		
		//Calculate n
		gen_n(p2, n);
		
		// If we find a n with enough solutions
		if(x2 >= bruteforce_l) {
			// If n is smaller then we already found
			if(mpz_cmp(bruteforce_n, n) > 0 || mpz_cmp_ui(bruteforce_n, -1) == 0) {
				mpz_set(bruteforce_n, n);
				
				//Debug
				//cout << mpz_get_str(nullptr, 10, n) << endl;
			}
		}
		/*
			If prime powers still generate a lower n then we already found
			we can bruteforce next level
		*/
		else if(mpz_cmp(bruteforce_n, n) > 0 || mpz_cmp_ui(bruteforce_n, -1) == 0) {
			bruteforce(p2, x2);
		}
	}
	
	mpz_clear(n);
}

/*
	generate n with the min solution
*/
string f(long long l) {
	string r;
	
	//Initialise settings to bruteforce
	bruteforce_l = (l * 2) - 1;
	mpz_init_set_ui(bruteforce_n, -1);

	//Bruteforce answer
	bruteforce({}, 1);
	
	//Convert to string
	r = mpz_get_str(nullptr, 10, bruteforce_n);
	
	//Clear
	mpz_clear(bruteforce_n);
	
	return r;
}

int main() {
	primes = IamLupo::Prime::generate(200);
	
	cout << "Result = " << f(4000000) << endl;
	
	/*
	cout << "f(1000)                = " << f(1000) << endl;
	cout << "f(4000000)             = " << f(4000000) << endl;
	cout << "f(1000000000)          = " << f(1000000000) << endl;
	cout << "f(1000000000000)       = " << f(1000000000000) << endl;
	cout << "f(1000000000000000)    = " << f(1000000000000000) << endl;
	cout << "f(1000000000000000000) = " << f(1000000000000000000) << endl;
	*/
	
	return 0;
}
