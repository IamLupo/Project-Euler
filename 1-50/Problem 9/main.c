#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
	a^2 + b^2 = c^2
	a + b + c = 1000
	a * b * c = product
	
	Conclusion:
	c = 1000 - a - b
	a^2 + b^2 = (1000 - a - b)^2
*/
int findABCProduct(int value, int* result) {
	int a, b, c;
	
	for(a = 0; a < value; a++) {
		for(b = a + 1; b < value - a - b; b++) {
			c = value - a - b;
			if(pow(a, 2) + pow(b, 2) == pow(c, 2)) {
				result[0] = a;
				result[1] = b;
				result[2] = c;
				
				return a * b * c;
			}
		}
	}
	
	return 0;
}

int main() {
	int product;
	int result[3];

	product = findABCProduct(1000, result);
	printf("the product of abc is %d * %d * %d = %d\n", result[0], result[1], result[2], product);
	
	return 0;
}