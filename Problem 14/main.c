#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "gmp.h"

/*
	Which starting number, under one million, produces the longest chain?
*/

struct Chain {
	int number;
	int rounds;
};

int getLongestChain(int max, struct Chain* result) {
	int i, round;
	uint64_t value;
	
	for(i = 1; i < max; i++) {
		value = i;
		round = 0;
		
		while(value != 1) {
			if(value % 2 == 0)
				value /= 2;
			else
				value = (value * 3) + 1;
			round++;
		}
		
		if(result->rounds < round) {
			result->number = i;
			result->rounds = round;
		}
	}
}

int main() {
	struct Chain result;
	
	getLongestChain(1000000, &result);
	
	printf("number = %d\n", result.number);
	printf("rounds = %d\n", result.rounds);
	
	return 0;
}