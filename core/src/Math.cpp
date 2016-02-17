#include "IamLupo/math.h"

/* Standard C Function: Greatest Common Divisor */
long long IamLupo::Math::gcd(long long a, long long b) {
	long long c;
	
	while ( a != 0 ) {
		c = a;
		a = b % a;
		b = c;
	}
	
	return b;
}

/* Recursive Standard C Function: Greatest Common Divisor */
long long IamLupo::Math::gcdr(long long a, long long b) {
	if (a == 0)
		return b;
	
	return gcdr(b % a, a);
}

long long IamLupo::Math::phi(long long n) {
	long long i, x;

	x = 0;

	for(i = 1; i <= n; i++)
		if(IamLupo::Math::gcd(n, i) == 1)
			x++;
	
	return x;
}