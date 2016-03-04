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
	Find the sum of the perimeters of all almost equilateral triangles
	with integral side lengths and area and whose perimeters do not exceed
	one billion (1,000,000,000).
*/

/*
	Almost equilateral triangle
	
	Data:
		5-5-6 has an area of 12 square units
		90 degree triangle { 6 / 2, sqrt(5^2 - (6/2)^2), 5 } = {3, 4, 5}
		area = 3 * 4 = 12
	
	Conclusion:
		First we make from the triangle settings 2 seperated triangles with 90 degree corner:
		
		x = (c + 1)/2
		b^2 = c^2 - x^2
		area = x * b
	
	Generated Data:
		These are some valid Almost equilateral triangle. But at higher scale
		the double will not be precise anymore.
		
		a		b		c
		3		4		5
		8		15		17
		33		56		65
		120		209		241
		451		780		901
		1680	2911	3361

	Conclusion:
		With Eureqa we can find a pattern in the data.
		This way we can keep working with integer variables.
		
		Init:
			a = 3
			b = 4
			c = 5
			
		Next:
			a = 2c + b - 2a
			b = 2c + 2b - a
			c = 3c + 2b - 2a
*/

struct Triangle {
	double a;
	double b;
	double c;
};

void generate(int l) {
	int i, r;
	double a;
	Triangle t;
	
	//Init
	i = 3;
	r = 0;
	
	while(r < l) {
		//Generate Triangle side A and C
		t.a = (i + 1) / 2;
		t.c = i;
		
		//Calculate Triangle side B with a 90 degree angle
		// A^2 + B^2 = C^2
		t.b = sqrt((t.c * t.c) - (t.a * t.a));
		
		//Calculate area
		a = t.a * t.b;
		
		//Check if area is integral
		if(a == round(a)) {
			r += (i * 3) + 1;
			cout << t.a << "	" << t.b << "	" << t.c << endl;
		}
		
		//Generate Triangle side A and C
		t.a = (i - 1.0) / 2;
		t.c = i;
		
		//Calculate Triangle side B with a 90 degree angle
		// A^2 + B^2 = C^2
		t.b = sqrt((t.c * t.c) - (t.a * t.a));
		
		//Calculate area
		a = t.a * t.b;
		
		//Check if area is integral
		if(a == round(a)) {
			r += (i * 3) - 1;
			cout << t.a << "	" << t.b << "	" << t.c << endl;
		}
		
		i++;
	}
}

int f(int l) {
	int a, b, c, r, t1, t2;
	
	r = 0;
	a = 3;
	b = 4;
	c = 5;
	
	while(r + ((a + c) * 2) < l) {
		//add the perimeters
		r += (a + c) * 2;
		
		//calculate next a, b and c
		t1 = (2 * c) + b - (2 * a);
		t2 = (2 * c) + (2 * b) - a;
		c = (3 * c) + (2 * b) - (2 * a);
		a = t1;
		b = t2;
	}
	
	return r;
}

int main() {
	//generate(5000);
	
	cout << "result = " << f(1000000000) << endl;
	
	return 0;
}
