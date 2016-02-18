#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int n, k, i, g, h;
    int p[60000] = {1, 1, 2, 3};

    for(n = 4; n < 60000; n++) {
        p[n] = 0;
		
        for (k = 1; k < n; k++) {
            i = (int)pow(-1, k - 1);
			g = k * (3 * k - 1) / 2;
			h = k * (3 * k + 1) / 2;

            if (g > n && h > n)
				break;
			
            if (g <= n)
				p[n] = (p[n] + i * p[n - g]) % 1000000;
            
			if (h <= n)
				p[n] = (p[n] + i * p[n - h]) % 1000000;
        }

        if (p[n] == 0) {
            cout << "Result: " << n << endl;
            break;
        }
    }
}