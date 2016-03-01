#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/math.h"

using namespace std;

/*
	Given that 0 ≤ x1, y1, x2, y2 ≤ 50, how many right triangles can be formed?
*/

int countRightTriangles(int v) {
	int x, y, f, r;
	
	r = v * v * 3;
	
	for(x = 1; x <= v; x++) {
		for(y = 1; y <= v; y++) {
			f = IamLupo::Math::gcd(x, y);
			r += min(y * f / x, (v - x) * f / y) * 2;
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << countRightTriangles(50) << endl;
	
	return 0;
}
