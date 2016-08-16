#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "gmp.h"
#include "IamLupo/vector.h"

using namespace std;

/*
	Plus:
	nonbouncy_range(100) = 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 = 45
	nonbouncy_range(200) = 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 = 36
	nonbouncy_range(300) = 7 + 6 + 5 + 4 + 3 + 2 + 1 = 28
	nonbouncy_range(400) = 6 + 5 + 4 + 3 + 2 + 1 = 21
	nonbouncy_range(500) = 5 + 4 + 3 + 2 + 1 = 15
	nonbouncy_range(600) = 4 + 3 + 2 + 1 = 10
	nonbouncy_range(700) = 3 + 2 + 1 = 6
	nonbouncy_range(800) = 2 + 1 = 3
	nonbouncy_range(900) = 1
	
	Minus:
	nonbouncy_range(100) = 1 + 2 = 3
	nonbouncy_range(200) = 1 + 2 + 3 = 6
	nonbouncy_range(300) = 1 + 2 + 3 + 4 = 10
	nonbouncy_range(400) = 1 + 2 + 3 + 4 + 5 = 15
	nonbouncy_range(500) = 1 + 2 + 3 + 4 + 5 + 6 = 21
	nonbouncy_range(600) = 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28
	nonbouncy_range(700) = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 = 36
	nonbouncy_range(800) = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 = 45
	nonbouncy_range(900) = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 = 55
*/

/* Development functions */
long long algo_plus(int v, int l, int m) {
	int i;
	long long r;
	
	if(l == m)
		return 1;
	
	//Init
	r = 0;
	
	for(i = v; i < 10; i++)
		r += algo_plus(i, l + 1, m);
	
	return r;
}

long long algo_plus2(const vector<int> &v, int l, int m) {
	int i;
	long long r;
	vector<int> v2;
	
	if(l == m) {
		for(i = 0; i < v.size(); i++)
			cout << v[i];
		cout << endl;
		
		return 1;
	}
	
	//Init
	r = 0;
	
	for(i = v[v.size() - 1]; i < 10; i++) {
		v2 = v;
		
		v2.push_back(i);
		
		r += algo_plus2(v2, l + 1, m);
	}
	
	return r;
}

long long algo_minus(int v, int l, int m) {
	int i;
	long long r;
	
	if(l == m)
		return 1;
	
	//Init
	r = 0;
	
	for(i = v; i >= 0; i--)
		r += algo_minus(i, l + 1, m);
	
	return r;
}

long long algo_minus2(const vector<int> &v, int l, int m) {
	int i;
	long long r;
	vector<int> v2;
	
	if(l == m) {
		for(i = 0; i < v.size(); i++)
			cout << v[i];
		cout << endl;
		
		return 1;
	}
	
	//Init
	r = 0;
	
	for(i = v[v.size() - 1]; i >= 0; i--) {
		v2 = v;
		
		v2.push_back(i);
		
		r += algo_minus2(v2, l + 1, m);
	}
	
	return r;
}

string test(int p) {
	int i, j;
	long long x;
	mpz_t r;
	string s;
	
	//Init
	mpz_init_set_ui(r, 1);
	
	for(i = 1; i <= p; i++) {
		for(j = 1; j < 10; j++) {
			
			//cout << "--- PLUS ---" << endl;
			x = algo_plus({j}, 1, i) - 1;
			//cout << "--- MINUS ---" << endl;
			x += algo_minus({j}, 1, i);
			
			//cout << x << endl;
			
			//r += x
			mpz_add_ui(r, r, x);
		}
		
		cout << "f(10^" << i << ") = " << mpz_get_str(nullptr, 10, r) << endl;
	}
	
	//Convert
	s = mpz_get_str(nullptr, 10, r);
	
	//Clear
	mpz_clear(r);
	
	return s;
}

/* Real solution */
vector<long long> update_plus(const vector<long long> &v) {
	int i, j, p;
	vector<long long> r;
	long long t;
	
	//Init
	p = v.size() - 1;
	
	for(i = 9; i > 0; i--) {
		t = 0;
		
		for(j = 0; j < i; j++)
			t += v[p - j];
		
		r.push_back(t);
	}
	
	return r;
}

vector<long long> update_minus(const vector<long long> &v) {
	int i, j, p;
	vector<long long> r;
	long long t;
	
	//Init
	p = v.size() - 1;
	
	for(i = 1; i <= v.size(); i++) {
		t = 0;
		
		for(j = 0; j < i; j++)
			t += v[j];
		
		r.push_back(t + 1);
	}
	
	return r;
}

void add(const vector<long long> &plus, const vector<long long> &minus, mpz_t output) {
	int i;
	
	for(i = 0; i < plus.size(); i++)
		mpz_add_ui(output, output, plus[i]);
	
	for(i = 0; i < minus.size(); i++)
		mpz_add_ui(output, output, minus[i]);
}

string f(int p) {
	int i;
	vector<long long> plus, minus;
	mpz_t r;
	string s;
	
	if(p == 1)
		return "10";
	
	//Init
	mpz_init_set_ui(r, 100);
	plus = {45, 36, 28, 21, 15, 10, 6, 3, 1};
	minus = {3, 6, 10, 15, 21, 28, 36, 45, 55};
	
	for(i = 2; i < p; i++) {
		//Add results
		add(plus, minus, r);
		
		// Remove duplicates
		mpz_sub_ui(r, r, 9);
		
		// Generate next level
		plus = update_plus(plus);
		minus = update_minus(minus);
	}
	
	//Remove 1 result because its lower then.
	mpz_sub_ui(r, r, 1);
	
	//Convert
	s = mpz_get_str(nullptr, 10, r);
	
	//Clean
	mpz_clear(r);
	
	return s;
}

int main() {
	cout << "Result = " << f(100) << endl;
	
	return 0;
}
