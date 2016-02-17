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