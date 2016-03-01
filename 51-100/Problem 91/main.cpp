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
	Given that 0 ≤ x1, y1, x2, y2 ≤ 50, how many right triangles can be formed?
*/

#define PI 3.14159265

struct Point {
	int x;
	int y;
};

struct Triangle {
	Point a;
	Point b;
	Point c;
};

double getBiggestAngle(Triangle &t) {
	double a, b, c, x;
	
	//Calculate triangle lengths
	a = sqrt(pow(t.a.x - t.c.x, 2) + pow(t.a.y - t.c.y, 2));
	b = sqrt(pow(t.b.x - t.a.x, 2) + pow(t.b.y - t.a.y, 2));
	c = sqrt(pow(t.b.x - t.c.x, 2) + pow(t.b.y - t.c.y, 2));
	
	//Calculate the largest angle
	if(a > b && a > c)
		x = (pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2 * b * c);
	else if(b > a && b > c)
		x = (pow(a, 2) + pow(c, 2) - pow(b, 2)) / (2 * a * c);
	else
		x = (pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b);
	
	//Convert with cos inverse
	return acos(x)  * 180.0 / PI;
}

int countRightTriangles(int v) {
	int i, j, s, r;
	double x;
	Triangle t;
	
	s = v + 1;
	r = 0;
	
	//Set point A to {0, 0}
	t.a.x = 0;
	t.a.y = 0;
	
	for(i = 1; i < s * s; i++) {
		//Generate Point B
		t.b.x = i / s;
		t.b.y = i % s;
		
		for(j = i + 1; j < s * s; j++) {
			//Generate Point C
			t.c.x = j / s;
			t.c.y = j % s;
			
			if(i != j) {
				//Calculate biggest angle
				x = getBiggestAngle(t);
				
				//Check results
				if(x < 90.01 && x > 89.99)
					r++;
				
				/*
				//Debug
				cout	<< "{" << t.a.x << "," << t.a.y << "} - "
						<< "{" << t.b.x << "," << t.b.y << "} - "
						<< "{" << t.c.x << "," << t.c.y << "} = " 
						<< getBiggestAngle(t) << endl;
				*/
			}
		}
	}
	
	return r;
}

int main() {
	cout << "result = " << countRightTriangles(50) << endl;
	
	return 0;
}
