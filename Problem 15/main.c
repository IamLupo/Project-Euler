#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "gmp.h"

/*
	How many routes are there through a 20×20 grid?
*/

void array_add2(uint64_t* array, int length) {
	int i;
	uint64_t temp[length];
	
	//Add bottom to top
	for(i = 0; i < length; i++) {
		temp[i] = array[i] + array[i + 1];
	}
	
	//Copy results
	for(i = 0; i < length; i++) {
		array[i] = temp[i];
	}
	
	array[length] = 0;
}

void array_add(uint64_t* array, int length) {
	int i;
	uint64_t temp[length];
	
	temp[0] = 1;
	temp[length] = 1;
	
	//Add bottom to top
	for(i = 0; i < length - 1; i++) {
		temp[i + 1] = array[i] + array[i + 1];
	}
	
	//Copy results
	for(i = 0; i < length + 2; i++) {
		array[i] = temp[i];
	}
}

uint64_t getRoutes2(int length) {
	int i, j;
	uint64_t values[length];
	
	memset(values, 0, length * sizeof(uint64_t));
	values[0] = 1;
	values[1] = 1;
	
	for(i = 2; i <= length; i++)
		array_add(values, i);
	
	for(i = length; i > 0; i--)
		array_add2(values, i);
	
	return values[0];
}

uint64_t getRoutes(int n) {
	int i;
	uint64_t result;
	
	result = 1;
	
	for(i = 1; i <= n; i++) {
		result += (result * n) / i;
		//result = result * (n + i) / i;
	}
	
	return result;
}

int main() {
	int i;
	
	for(i = 0; i < 20; i++)
		printf("%d	%lld\n", i, getRoutes(i));
	
	return 0;
}