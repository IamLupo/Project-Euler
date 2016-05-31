#include <stdio.h>
#include <math.h>

// Returns true if a and b are the basis for a pythagorean triple
bool is_pythagorean_triple(int a, int b) {
    int c, c2;
	
	c2 = a * a + b * b;
    c = sqrt(c2);
	
    return c * c == c2;
}

// Given that b1,b2<a, find the total number of distinct variations
// where b1 + b2 = b;
int b1_b2_possibilities(int a, int b) {
    if(a >= b)
        a = b - 1;
	
    return (a - ((b - 1) / 2));
}

int main() {
	int a, b, count;
	
	//Init
	count = 0;
	a = 0;
	
	do {
		a++;
		
		for(b = 2; b <= 2 * a; b++)
			if(is_pythagorean_triple(a, b))
				count += b1_b2_possibilities(a, b);
	} while (count < 1000000);
	
	printf("%d\n", a);
}
