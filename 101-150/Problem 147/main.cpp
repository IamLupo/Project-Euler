#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>

using namespace std;

/*
	How many different rectangles could be situated within 47x43 and smaller grids?
*/

/*
	Conclusion A:
		Straight Grid with same x and y can be calculated with:
		
		Formula:
			(n*(n+1)/2)^2
		
		Reference:
			http://oeis.org/A000537
	
	Conclusion B:
		While generating "data.txt" i found a pattern in the data. I noticed a
		repeating pattern in the grid. Higher x and y grids had the same values
		as lower ones but with a extra "z" value.
		
		Formula:
			grid(x, y) = grid(x - 1, y - 1) + z
		
	Conclusion C:
		With variable "z" in mind i notice this variable exist of a starting
		position for a range with two extra variables "d"(distance) and "r"(start).
		
		Formula:
			z = r + r - d
			
		"r" could be generated based on the diagonal lines and add them to the
		range function.
		
		"d" could be generated based on the longest diagonal length.
	
	Conclusion D:
		With "z" i could generate all grids that had the same x and y values.
		But for others there was a increasing patterm.
		
		Data:
			1: +1
			2: +9
			3: +25
			4: +49
		
		Formula:
			f(x) = range((x * 2) - 1) + range((x * 2) - 2)
		
		With the increasing pattern, the starting position and the grids with the same
		x and y, I could generate diagonal values.
*/
struct Grid {
	int x;
	int y;
};

typedef vector<vector<int>> Diagonal;

static Diagonal diagonal;

/*
	f(x) = 1 + 2 + 3 + ... + x
	
	Example:
		f(6) = 1 + 2 + 3 + 4 + 5 + 6 = 21
*/
long long range(int n) {
	if(n == 1)
		return 1;
	
	if(n % 2 == 1)
		return ((n / 2) * (n + 1)) + (n / 2) + 1;
	else
		return (n / 2) * (n + 1);
}

/*
	Calculates the max diagonal length of grid
*/
int max(int v) {
	if(v == 1)
		return 1;
	else
		return ((v - 2) * 2) + 3;
}

/*
	For every grid(x, x) these has to be a starting value for diagonal line
*/
long long start(int x) {
	int i;
	long long d, r;
	
	//Init 
	r = 0;
	d = range(max(x) - 1);
	
	for(i = 1; i < x; i++)
		r += range(i * 2);
	
	r *= 2;
	
	return r + r - d;
}

/*
	Calcualte diagonal grids
*/
Diagonal generate(const Grid &g) {
	int x, y, s, m;
	long long v, p1, p2;
	
	//Init
	m = (g.x > g.y) ? g.x : g.y;
	Diagonal r(m + 1, vector<int>(m + 1, 0));
	
	for(y = 1; y <= m; y++) {
		//Init
		v = start(y);
		
		for(x = y; x <= m; x++) {
			if(y == 1) {
				r[x][y] = x - 1;
				r[y][x] = x - 1;
			} else {
				s = (x - y);
				p1 = range((y * 2) - 1);
				p2 = range((y * 2) - 2);
				
				r[x][y] = r[x - 1][y - 1] + v + s * p1 + s * p2;
				r[y][x] = r[x - 1][y - 1] + v + s * p1 + s * p2;
			}
		}
	}
	
	return r;
}

long long calc_grid(const Grid &g) {
	int x, y, px, py;
	long long r, v;
	
	//Init
	r = 0;
	
	//Vertical and horizontal
	for(y = 1; y <= g.y; y++) {
		for(x = 1; x <= g.x; x++) {
			px = g.x - x + 1;
			py = g.y - y + 1;
			
			r += px * py;
			
			//Debug
			//cout << px * py << "(" << x << "x" << y << ")" << endl;
		}
	}
	
	//Diagonal
	r += diagonal[g.x][g.y];
	
	return r;
}

long long f(const Grid &g) {
	int x, y;
	long long n, r;
	
	//Init
	r = 0;
	diagonal = generate(g);
	
	for(y = 1; y <= g.y; y++)
		for(x = 1; x <= g.x; x++) {
			n = calc_grid({x, y});
			
			r += n;
			
			//Debug
			//cout << n << "(" << x << "x" << y << ")" << endl;
		}
	
	return r;
}

int main() {
	cout << "Result = " << f({47, 43}) << endl;
	
	return 0;
}
