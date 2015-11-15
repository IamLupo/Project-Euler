#include <stdio.h>

int multiplesSum(int nr) {
	int i, sum;
	
	sum = 0;
	
	for(i = 0; i < nr; i++) {
		if(i % 3 == 0 || i % 5 == 0)
			sum += i;
	}
	
	return sum;
}

int main() {
	printf("sum = %d\n", multiplesSum(10));
	printf("sum = %d\n", multiplesSum(1000));
}