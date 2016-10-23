#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/sqrt.h"
#include "IamLupo/math.h"

using namespace std;

/*
	Find the smallest x + y + z with integers x > y > z > 0 such that
	x + y, x − y, x + z, x − z, y + z, y − z are all perfect squares.
*/

/*
	Rules:
		x > y > z > 0
		
		x + y
		x + z
		y + z
		
		x − y
		x − z
		y − z
	
	Conclusion:
		a^2 = x + y
		b^2 = x + z
		c^2 = x − y
		
		a^2 + c^2 = 2x
		a^2 - c^2 = 2y
		
	Conclusion:
		a^2 = x + z
		b^2 = x + y
		c^2 = x − z
		
		a^2 + c^2 = 2x
		a^2 - c^2 = 2z
*/

long long f() {
	long long a, a2, b, c, x, y, z;
	
	for(a = 1; a < 1000; a++) {
		a2 = a * a;
		for(c = a - 2; c > 0; c -= 2) {
			x = (a2 + (c * c)) / 2;
			y = (a2 - (c * c)) / 2;
			
			if(IamLupo::Sqrt::is(x + y) && IamLupo::Sqrt::is(x - y)) {
				for(b = sqrt(x); b < a; b++) {
					z = (b * b) - x;
					
					if( IamLupo::Sqrt::is(x + z) &&
						IamLupo::Sqrt::is(x - z) &&
						IamLupo::Sqrt::is(y + z) &&
						IamLupo::Sqrt::is(y - z)) {
						
						//Debug
						cout << x << ", " << y << ", " << z << endl;
						
						return x + y + z; //Found
					}
					
				}
			}
		}
	}
	
	return -1; // Unknown
}

int main() {
	cout << "Result = " << f() << endl;
	
	return 0;
}
