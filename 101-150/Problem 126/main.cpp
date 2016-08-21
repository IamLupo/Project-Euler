#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	Find the least value of n for which C(n) = 1000.
*/

static int limit = 20000;

long long cubes(int x, int y, int z, int n) {
	return 2 * (x * y + y * z + x * z ) + 4 * (x + y + z + n - 2) * (n - 1);
}

int f(int l) {
	int x, y, z, n;
	vector<int> r(limit + 1, 0);
	
	for(x = 1; cubes(x, 1, 1, 1) <= limit; x++)
		for(y = 1; y <= x && cubes(x, y, 1, 1) <= limit; y++)
			for(z = 1; z <= y && cubes(x, y, z, 1) <= limit; z++)
				for(n = 1; cubes(x, y, z, n) <= limit; n++)
					r[cubes(x, y, z, n)]++;
	
	for(x = 0; x < r.size(); x++)
		if(r[x] == l)
			return x;
		
	return -1; // Limit is to low
}

int main() {
	cout << "Result = " << f(1000) << endl;
	
	return 0;
}
