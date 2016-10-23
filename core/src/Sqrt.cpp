#include <math.h>

#include "IamLupo/sqrt.h"

bool IamLupo::Sqrt::is(long long n) {
	if (n < 0)
		return false;

	long long x = sqrt(n);
	
	return x * x == n;
}

/*
	Continued fraction expansion
	
	https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Continued_fraction_expansion
*/

IamLupo::Sqrt::CFraction IamLupo::Sqrt::ContinuedFraction(long long s) {
	int i;
	long long m, d, a0, a, x, y, z;
	IamLupo::Sqrt::CFraction r;
	
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

/*
	Exponential e
*/

IamLupo::Sqrt::ExponentialE IamLupo::Sqrt::Expo_Init(const IamLupo::Sqrt::CFraction &fr) {
	IamLupo::Sqrt::ExponentialE r;
	
	//Positions
	mpz_init_set_ui(r.x1, 1);
	mpz_init_set_ui(r.x2, fr[0]);
	mpz_init_set_ui(r.y1, 0);
	mpz_init_set_ui(r.y2, 1);
	
	//Copy fraction
	r.fr = fr;
	
	//Start at level 1
	r.level = 0;
	
	return r;
}

void IamLupo::Sqrt::clear(IamLupo::Sqrt::ExponentialE &r) {
	mpz_clear(r.x1);
	mpz_clear(r.x2);
	mpz_clear(r.y1);
	mpz_clear(r.y2);
}

void IamLupo::Sqrt::Expo_Next(IamLupo::Sqrt::ExponentialE &exp) {
	mpz_t t;
	
	mpz_init(t);
	
	//Generate x
	//t = x2
	mpz_set(t, exp.x2);
	
	mpz_mul_ui(exp.x2, exp.x2, exp.fr[exp.level + 1]);
	mpz_add(exp.x2, exp.x2, exp.x1);
	
	//y1 = t
	mpz_set(exp.x1, t);
	
	//Generate y
	//t = y2
	mpz_set(t, exp.y2);
	
	//y2 = (y2 * v) + y1
	mpz_mul_ui(exp.y2, exp.y2, exp.fr[exp.level + 1]);
	mpz_add(exp.y2, exp.y2, exp.y1);
	
	//y1 = t
	mpz_set(exp.y1, t);
	
	//Next id
	exp.level = (exp.level + 1) % (exp.fr.size() - 1);
	
	mpz_clear(t);
}