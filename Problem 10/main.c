#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t sumPrimes(int limit) {
	unsigned long long int i, j;
	int *primes;
	uint64_t sum;
	
	//Init
	sum = 0;
	primes = malloc(sizeof(int) * limit);

	//Enable all numbers
	for(i = 2; i < limit; i++)
		primes[i] = 1;

	//Disable all none primes
	for(i = 2; i < limit; i++)
		if(primes[i])
			for(j = i; i * j < limit; j++)
				primes[i * j] = 0;

	//Sum all Primes
	for(i = 2; i < limit; i++)
		if(primes[i])
			sum += i;
	
	//Clean
	free(primes);
	
	return sum;
}

int main() {
	printf("sum = %lld\n", (long long)sumPrimes(2000000));
	
	return 0;
}