#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

void generatePrimes(int limit, int** primes) {
	unsigned long long int i, j, last_index, crosslimit;
	
	//Init
	last_index = (limit - 1) / 2;						// remove all even numbers and 1;
	crosslimit = (floor(sqrt(limit)) - 1) / 2;
	
	*primes = (int*)calloc(last_index, sizeof(int));

	//Disable all none primes
	for(i = 1; i < crosslimit; i++)
		if((*primes)[i] == 0)
			for(j = 2 * i * ( i + 1); j < last_index; j += 2 * i + 1)
				(*primes)[j] = 1;
	
}

uint64_t sumPrimes(int limit) {
	unsigned long long int i, last_index;
	int* primes;
	uint64_t sum;
	
	sum = 2;
	last_index = (limit - 1) / 2;
	
	generatePrimes(limit, &primes);
	
	for(i = 1; i < last_index; i++)
		if(primes[i] == 0)
			sum += (2 * i) + 1;
		
	//Clean
	free(primes);
	
	return sum;
}

int main() {
	printf("sum = %lld\n", (long long)sumPrimes(2000000));
	
	return 0;
}