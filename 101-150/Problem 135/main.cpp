#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"
#include "IamLupo/prime.h"

using namespace std;

/*
	How many values of n less than one million have exactly ten distinct solutions?
*/

/*
	Formula:
		n = x^2 - y^2 - z^2 
		
		x^2 > n
		y >= n
		
		n dividers must be 10 or higher
		
	Data:
		4^2 - 3^2 - 2^2 = 3
		3^2 - 2^2 - 1^2 = 4
		9^2 - 7^2 - 5^2 = 7
		14^2 - 11^2 - 8^2 = 11
		8^2 - 6^2 - 4^2 = 12
		5^2 - 3^2 - 1^2 = 15
		7^2 - 5^2 - 3^2 = 15
		19^2 - 15^2 - 11^2 = 15
		6^2 - 4^2 - 2^2 = 16
		24^2 - 19^2 - 14^2 = 19
		13^2 - 10^2 - 7^2 = 20
		29^2 - 23^2 - 17^2 = 23
		34^2 - 27^2 - 20^2 = 27
		12^2 - 9^2 - 6^2 = 27
		18^2 - 14^2 - 10^2 = 28
		39^2 - 31^2 - 23^2 = 31
		7^2 - 4^2 - 1^2 = 32
		11^2 - 8^2 - 5^2 = 32
		8^2 - 5^2 - 2^2 = 35
		10^2 - 7^2 - 4^2 = 35
		44^2 - 35^2 - 26^2 = 35
		9^2 - 6^2 - 3^2 = 36
		23^2 - 18^2 - 13^2 = 36
		17^2 - 13^2 - 9^2 = 39
		49^2 - 39^2 - 29^2 = 39
		54^2 - 43^2 - 32^2 = 43
		28^2 - 22^2 - 16^2 = 44
		59^2 - 47^2 - 35^2 = 47
		16^2 - 12^2 - 8^2 = 48

	Conclusion A:
		y = divisers of n
		d = distance between x, y and z
		
		d = (y / 4) + (n / 4y)
		
		x = y + d
		z = y - d
		
		Prove:
			We want to know n = 7
			
			7 has 1 diviser thats 7
			
			d = (7 / 4) + (7 / 28) = (49 / 28) + (7 / 28) = 56 / 28 = 2
			
			x = 7 + 2
			y = 7
			z = 7 - 2
			
			Result:
				7 = 9^2 - 7^2 - 5^2
*/

vector<vector<int>> dividers(int l) {
	int i, j;
	vector<vector<int>> r(l + 1);
	
	for(i = 2; i <= l; i++)
		for(j = i; j <= l; j += i)
			r[j].push_back(i);
	
	return r;
}

/*
	r = (a / b) + (c / d) = (a * d) + (c * b)) / (b * d) = x + y / z
*/
long long sum(int a, int b, int c, int d) {
	long long r;
	mpz_t x, y, z;
	
	//Init
	mpz_init_set_ui(x, a);
	mpz_init_set_ui(y, c);
	mpz_init_set_ui(z, b);
	
	//x = a * d
	mpz_mul_ui(x, x, d);
	
	//y = c * b
	mpz_mul_ui(y, y, b);
	
	//z = b * d
	mpz_mul_ui(z, z, d);
	
	//x + y / z
	mpz_add(x, x, y);
	mpz_div(x, x, z);
	
	//Conver
	r = mpz_get_ui(x);
	
	//Clean
	mpz_clear(x);
	mpz_clear(y);
	mpz_clear(z);
	
	return r; //((a * d) + (c * b)) / (b * d)
}

long long f(int l) {
	int i, j, c, d, r, x, y, z;
	long long v;
	vector<vector<int>> div;
	
	//Init
	r = 0;
	div = dividers(l);
	
	for(i = 2; i < div.size(); i++) {
		if(div[i].size() >= 10) {
			c = 0;
			
			for(j = 0; j < div[i].size() && c <= 10; j++) {
				y = div[i][j];
				
				//d = (y / 4) + (n / 4y)
				d = sum(y, 4, i, 4 * y);
				
				if(y - d > 0) {
					//Update x and y
					x = y + d;
					z = y - d;
					
					v = pow(x, 2) - pow(y, 2) - pow(z, 2);
					
					//Check result
					if(v == i) {
						c++;
						
						//Debug
						//cout << x << "^2 - " << y << "^2 - " << z << "^2 = " << i << endl;
					}
				}
			}
			
			//cout << c << endl;
			
			if(c == 10) {
				r++;
				
				//Debug
				//cout << i << " = " << div[i].size() << endl;
			}
		}
	}
	
	return r;
}

int main() {
	cout << "Result = " << f(1000000) << endl;
	
	return 0;
}
