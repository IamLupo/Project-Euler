#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool IsPrime(int number) {
    int i;
    
	for(i = 2; i < number; i++) {
        if(number % i == 0 && i != number)
			return false;
    }
	
    return true;
}

int nextPrime(int prime) {
	int next = prime + 1;
	
	while(!IsPrime(next))
		next++;
		
	return next;
}

int findLargestPrimeFactor(uint64_t nr) {
	int prime = 2;
	uint64_t sum = nr;
	
	while(sum != prime) {
		if(sum % prime == 0)
			sum /= prime;
		
		prime = nextPrime(prime);
	}
	
	return prime;
}

int main() {
	printf("largest prime factor = %d\n", findLargestPrimeFactor(600851475143));
	
	return 0;
}