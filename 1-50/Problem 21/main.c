#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

/*
	Evaluate the sum of all the amicable numbers under 10000.
*/
int d(int x) {
	int sum, i;
	
	sum = 1;
	
	for(i = 2; i <= (x / 2); i++)
		if(x % i == 0)
			sum += i;
	
	return sum;
}

int sumAmicable(int x) {
	int sum, i, value;
	
	sum = 0;
	
	for(i = 1; i < x; i++) {
		value = d(i);
		if(i == d(value) && i != value)
			sum += i;
	}
	
	return sum;
}

int main() {
	printf("sum = %d\n", sumAmicable(10000));
	
	return 0;
}