#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>

#include "IamLupo/sqrt.h"
#include "IamLupo/math.h"

using namespace std;

/*
	Find the sum of all distinct values of p + q + r ≤ 120000 for Torricelli triangles.
*/

/*
	Conclusion A:
		By testing the example a = 399, b = 455, c = 511, pqr = 784. We notice that
		p = 195, q = 264 and r = 325. (See example function)
		
		By better analising we notice that the angle of the ATC = CTB = ATB = 120 degrees.
		This makes we can bruteforce q and r and check it generated a as a integer.
		We can use the SAS function to calculate this.
		
		Formula:
			c^2 = a^2 + b^2 − (2ab * cos(120 * PI / 180))
		
	Conclusion B:
		After better analising the SAS formula i noticed:
			cos(120 * PI / 180) = -0.5
			
		This changed the SAS function to:
			c^2 = a^2 + b^2 + ab
	
	Documentation:
		https://en.wikipedia.org/wiki/Fermat_point
		http://www.calculator.net/triangle-calculator.html?vc=120&vx=264&vy=195&va=&vz=&vb=&angleunits=d&x=63&y=19
		http://mste.illinois.edu/courses/ci336sp04/folders/ckoeppen/5dayunit/lesson1.html
*/

#define RAD_TO_DEG M_PI * 180
#define DEG_TO_RAD M_PI / 180

/* -------------- Example --------------------- */

struct Triangle {
	//Lengths
	int x;
	int y;
	int z;
	
	//Radian
	double a;
	double b;
	double c;
};

void draw(const Triangle &t, const string text = "") {
	if(text != "")
		cout << text << ":" << endl
			 << "  Length: " << t.x << ", " << t.y << ", " << t.z << endl
			 << "  Degree: " << t.a << ", " << t.b << ", " << t.c << endl;
	else
		cout << "Length: " << t.x << ", " << t.y << ", " << t.z << endl
			 << "Degree: " << t.a << ", " << t.b << ", " << t.c << endl;
}

void get_degree(Triangle &t) {
	t.a = acos((pow(t.x, 2) + pow(t.z, 2) - pow(t.y, 2))/(2 * t.x * t.z));
	t.b = acos((pow(t.x, 2) + pow(t.y, 2) - pow(t.z, 2))/(2 * t.x * t.y));
	t.c = acos((pow(t.y, 2) + pow(t.z, 2) - pow(t.x, 2))/(2 * t.y * t.z));
	
	//Convert Rad to Deg
	t.a = t.a / RAD_TO_DEG;
	t.b = t.b / RAD_TO_DEG;
	t.c = t.c / RAD_TO_DEG;
}

long long example(const Triangle &t, int pqr) {
	int p, q, r;
	Triangle tr_h, tr_a, tr_b, tr_c;
	double v;
	
	//Init
	tr_h = t;
	get_degree(tr_h);
	
	for(p = 1; p + 2 <= pqr; p++) {
		for(q = 1; p + q + 1 <= pqr; q++) {
			r = pqr - p - q;
			
			//Set Triangle A
			tr_a.x = p;
			tr_a.y = tr_h.z;
			tr_a.z = r;
			
			//Set Triangle B
			tr_b.x = r;
			tr_b.y = tr_h.x;
			tr_b.z = q;
			
			//Set Triangle C
			tr_c.x = q;
			tr_c.y = tr_h.y;
			tr_c.z = p;
			
			get_degree(tr_a);
			get_degree(tr_b);
			get_degree(tr_c);
			
			if(!isnan(tr_a.a) && !isnan(tr_b.a) && !isnan(tr_c.a)) {
				v = tr_a.a + tr_b.a + tr_c.a;
				
				if(v < 360.001 && v > 359.999) {
					//Debug
					draw(tr_h, "Head Triangle");
					draw(tr_a, "Triangle A");
					draw(tr_b, "Triangle B");
					draw(tr_c, "Triangle C");
					
					cout << "Result:" << endl;
					cout << "  Triangle A+B+C Degree: " << v << endl;
					cout << "  pqr: " << p << ", " << q << ", " << r << endl;
					
					cout << "---------------------" << endl;
				}
			}
		}
	}
	
	return -1; // Unknown
}

/* -------------- REAL --------------------- */
/*
	Triange: Side, Angle, Side
	
	Formula:
		c^2 = a^2 + b^2 + ab
	
	Reference:
		https://www.mathsisfun.com/algebra/trig-solving-sas-triangles.html
*/
long long sas(long long a, long long b) {
	return sqrt((a * a) + (b * b) + (a * b));
}

bool is_sas(long long a, long long b) {
	return IamLupo::Sqrt::is((a * a) + (b * b) + (a * b));
}

int f(int l) {
	int a, b, c, p, q, r;
	set<int> s;
	//Debug
	cout << "p	q	r	pqr	a	b	c" << endl;
	
	for(p = 1; p + p + p + 3 <= l; p++) {
		for(q = p + 1; p + q + q + 1 <= l; q++) {
			if(is_sas(p, q)) {
				for(r = q + 1; q + p + r <= l; r++) {
					if(is_sas(q, r) && is_sas(p, r)) {
						s.insert(p + q + r);

						a = sas(p, q);
						b = sas(r, p);
						c = sas(q, r);
						
						//Debug
						cout << p << "	" << q << "	" << r << "	"
							 << (p + q + r) << "	"
							 << a << "	"
							 << b << "	"
							 << c << "	"
							 << endl;
					}
				}
			}
		}
	}
	
	return accumulate(s.begin(), s.end(), 0);
}

int main() {
	//example({399, 455, 511}, 784);
	
	cout << "Result = " << f(120000) << endl;
	
	return 0;
}
