// MAde by Proutsalut

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

long long int listDivisors(long long int a, int target){
	long long int j, i;
	
	j = 0;
	for(i = 2; i < a + 2; i++) {
		if(a % i == 0) {
			j++;
		}
	}

	printf("::%lld", j + 1);
	
	if(j >= target)
		exit(1);
	
	return 0;
}

long long int triangleNumbers(int target){
	int i;
	long long int value = 0;
	
	for(i = 1; i <= 20000; i++) {
		value += i;

		if(value % target == 0) {
			printf("%lld:", value);
			listDivisors(value, target);

			printf("..%d\n\n",i);
		}
	}
	
	return value;
}

int main() {
	long long int value;
	value = triangleNumbers(500);
}