#include <stdio.h>
#include <math.h>

// Returns true if a and b are the basis for a pythagorean triple
int is_pythagorean_triple(int a, int b) {
    int c2 = a*a + b*b;
    int c = sqrt(c2);
    return c*c == c2;
}

// Given that b1,b2<a, find the total number of distinct variations
// where b1 + b2 = b;
int b1_b2_possibilities(int a, int b) {
    if (a>=b)
        a = b-1;
    return (a - ((b-1)/2));
}

int main() {
    int count = 0;
    int a = 0,b;

    do {
        a++;
        for (b=2;b<=2*a;b++) {
            if (is_pythagorean_triple(a, b)) {
                count += b1_b2_possibilities(a, b);
            }
        }
    } while (count < 1000000);
    
    printf("%d\n", a);
}
