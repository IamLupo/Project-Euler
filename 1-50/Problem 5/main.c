#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

bool IsPrime(int number) {
    int i;
    
	for(i = 2; i < number; i++) {
        if(number % i == 0 && i != number)
			return false;
    }
	
    return true;
}

int findPrimeFactorInArray(int number, int* primes, int primes_length, int* result_primes_used) {
	int i;
	
	for(i = 0; i < primes_length; i++) {
		if(number % primes[i] == 0) {
			result_primes_used[i]++;
			return i;
		}
	}
	
	return -1;
}

int divisionMinimalRange(int min, int max) {
	int i, number, id, sum, primes_length;
	int* primes;
	int* primes_used;
	int* result_primes_used;
	
	//Init
	sum = 1;
	primes = (int*)malloc((max - min) * sizeof(int));
	primes_used = (int*)calloc((max - min), sizeof(int));
	primes_length = 0;
	
	//Get Prime Numbers out of range
	for(i = min; i < max; i++) {
		if(i != 1 && IsPrime(i)) {
			primes[primes_length] = i;
			primes_used[primes_length] = 1;
			primes_length++;
			
			sum *= i;
		}
		else
		{
			//Init
			number = i;
			result_primes_used = (int*)calloc(primes_length, sizeof(int));
			
			id = findPrimeFactorInArray(number, primes, primes_length, result_primes_used);
			while(id != -1) {
				number /= primes[id];
				
				if(result_primes_used[id] > primes_used[id]) {
					sum *= primes[id];
					primes_used[id]++;
				}
				
				id = findPrimeFactorInArray(number, primes, primes_length, result_primes_used);
			}
			
			sum *= number;
			
			//Free
			free(result_primes_used);
		}
	}
	
	return sum;
}

int main() {
	/*
		My conclusion:
		Prime: 2, 3, 5, 7
		Not Prime: 1, 4, 6, 8, 9, 10
		
		Case:
			1 = 1		number already exist
			4 = 2 * 2	number 2 exist once, we need to add * 2 to our sum
			6 = 2 * 3	numbers already exist
			8 = 4 * 2 	number 4 exist once, we need to add * 2 to our sum
			9 = 3 * 3	number 3 exist once, we need to add * 3 to our sum
			10 = 5 * 2	numbers already exist
			
		2520 =	1 * 2 * 3 * 2 * 5 * 1 * 7 * 2 * 3 * 1
	*/
	printf("answer = %d\n", divisionMinimalRange(1, 10));
	
	//Challange
	/*
		Prime: 2, 3, 5, 7, 11, 13, 17, 19
		
		Case:
			12 = 3 * 4	numbers already exist
			14 = 2 * 7  numbers already exist
			15 = 5 * 3	numbers already exist
			16 = 8 * 2 	number 8 exist once, we need to add * 2 to our sum
			18 = 9 * 2	numbers already exist
			20 = 5 * 4	numbers already exist
		
		232792560 = 2520 * 11 * 13 * 17 * 19 * 2
	*/
	printf("answer = %d\n", divisionMinimalRange(1, 20));
	
	return 0;
}