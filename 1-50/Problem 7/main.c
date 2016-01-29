#include <stdio.h>
#include <stdlib.h>

#define LIMIT 1000000

int main() {
	unsigned long long int i, j;
	int *primes;
	int z = 0;
	
	primes = malloc(sizeof(int) * LIMIT);

	for(i = 2; i < LIMIT; i++)
		primes[i] = 1;

	for(i = 2; i < LIMIT; i++)
		if(primes[i])
			for(j = i; i * j < LIMIT; j++)
				primes[i * j] = 0;

	for(i = 2; i < LIMIT; i++)
		if(primes[i]) {
			z++;
			if(z == 10001)
				printf("%dth prime is %d\n", z, (int)i);
		}
	free(primes);
	
	return 0;
}