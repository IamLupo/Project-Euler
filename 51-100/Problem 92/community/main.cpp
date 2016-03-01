#include <stdio.h>

int chain(int n) {
	int digit, next = 0;

	while(n) {
		digit = n % 10;
		next += digit * digit;
		n /= 10;
	}
	
	if(next == 89)
		return 1;
	else if (next == 1)
		return 0;
	else
		return chain(next);
}

int main(void) {
	int i, count = 0;

	for (i = 1; i < 10000000; i++)
		count += chain(i);

	printf("Count: %d\n", count);

	return 0;
}