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

/*
	https://en.wikipedia.org/wiki/Euler's_totient_function#Euler.27s_product_formula
	http://www.algorithmist.com/index.php/Euler's_Phi_function
*/
long long IamLupo::Math::phi(long long n) {
	long long r;
	long long i;

	if(n == 1)
		return 1;

	r = n;

	/*
		Check for divisibility by every prime number below the square root.
		Start with 2.
	*/
	if(n % 2 == 0) {
		r -= r/2;
		do {
			n /= 2;
		} while(n % 2 == 0);
	}

	/*
		Since this doesn't use a list of primes, check every odd number.
		Ideally, skip past composite numbers.
	*/
	for(i = 3; i * i <= n; i += 2) {
		if(n % i == 0) {
			r -= r / i;
			do {
				n /= i;
			} while(n % i == 0) ;
		}
	}
	
	/*
		If n > 1, then it's the last factor at this point.
	*/
	if(n > 1)
		r -= r / n;
	
	return r; 
}


/*
	https://en.wikipedia.org/wiki/Factorial
*/
long long IamLupo::Math::factorial(long long n) {
	long long i, r;
	
	r = 1;
	
	for(i = 2; i <= n; i++)
		r *= i;
	
	return r;
}

/*
	https://nl.wikipedia.org/wiki/Binomiaalco%C3%ABffici%C3%ABnt
*/
long long IamLupo::Math::binomial_coefficient(unsigned long n, unsigned long k) {
    unsigned long i;
    long long b;
	
    if (0 == k || n == k)
        return 1;
    
    if (k > n)
        return 0;
    
    if (k > (n - k))
        k = n - k;
    
    if (1 == k)
        return n;
    
    b = 1;
    for (i = 1; i <= k; ++i) {
        b *= (n - (k - i));
		
        if (b < 0)
			return -1; /* Overflow */
        
		b /= i;
    }
	
    return b;
}
