#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/string.h"
#include "IamLupo/number.h"

using namespace std;

/*
	Find the number of triangles for which the interior contains the origin.
*/

/*
	Cartesian plane:
		https://www.mathsisfun.com/data/cartesian-coordinates-interactive.html
	
	Data:
		Triangle ABC:
			(-340,500), (-150,-910), (840,-950) has (0, 0) inside the triangle
		
		Triangle XYZ:
			(-175, 41), (-421, -714), (574, -645) has not (0, 0) inside the triangle
*/

struct Point {
	int x;
	int y;
};

struct Triangle {
	Point a;
	Point b;
	Point c;
};

vector<Triangle> readFile(const string &f) {
	string v;
	vector<string> l;
	Triangle t;
	vector<Triangle> r;
	ifstream file(f);
	
	if(file.is_open()) {
		while(file.good()) {
			//First line is trash
			getline(file, v);
			l = IamLupo::String::explode(v, ',');
			
			//get the points positions
			if(l.size() == 6) {
				t.a.x = IamLupo::Number::to(l[0]);
				t.a.y = IamLupo::Number::to(l[1]);
				t.b.x = IamLupo::Number::to(l[2]);
				t.b.y = IamLupo::Number::to(l[3]);
				t.c.x = IamLupo::Number::to(l[4]);
				t.c.y = IamLupo::Number::to(l[5]);
			}
			
			//save Triangle
			r.push_back(t);
		}
	}
	
	file.close();
	
	return r;
}

int sign(const Point &p1, const Point &p2, const Point &p3) {
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool isInside(const Triangle &t, const Point &pt) {
    bool b1, b2, b3;

    b1 = sign(pt, t.a, t.b) < 0;
    b2 = sign(pt, t.b, t.c) < 0;
    b3 = sign(pt, t.c, t.a) < 0;

    return ((b1 == b2) && (b2 == b3));
}

int countTriangleInCenter(const string &f) {
	int i, r;
	vector<Triangle> t;
	
	//Init
	r = 0;
	t = readFile(f);
	
	for(i = 0; i < t.size() ; i++)
		if(isInside(t[i], {0, 0}))
			r++;
	
	return r;
}

int main() {
	cout << "result = " << countTriangleInCenter("triangles.txt") << endl;
	
	return 0;
}
