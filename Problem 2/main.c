#include <stdio.h>

int findFibonacciEvenTermsSum(int max_nr) {
	int x, y, temp, sum;
	
	sum = 0;
	x = 1;
	y = 1;
	
	while(sum < max_nr) {
		temp = x + y;
		x = y;
		y = temp;
		
		if((y & 1) == 0) {
			printf("Found Even Fibonacci number %d\n", y);
			sum += y;
		}
	}
	
	return sum;
}

int main() {
	printf("sum = %d\n", findFibonacciEvenTermsSum(4000000));
}