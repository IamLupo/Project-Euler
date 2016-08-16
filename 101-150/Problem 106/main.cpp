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
	For n = 12, how many of the 261625 subset pairs that can
	be obtained need to be tested for equality?
*/

typedef vector<int> Subset;
typedef vector<vector<int>> Subsets;

void draw(const Subset &s) {
	int i;
	
	cout << "{";
	
	for(i = 0; i < s.size(); i++) {
		cout << s[i];
		
		if(i + 1 != s.size())
			cout << ", ";
	}
	
	cout << "}";
}

int S(const Subset &v) {
	return accumulate(v.begin(), v.end(), 0);
}

/*
	Example:
		f({1, 2, 3}, {4}) = true because 4 is not in the other list
		f({1, 2, 3}, {2}) = false because 2 is in the other list
*/
bool uniek(const Subset &a, const Subset &b) {
	int x, y;
	
	//Init
	x = 0;
	y = 0;
	
	while(x < a.size() && y < b.size()) {
		if(a[x] == b[y])
			return false;
		
		if(a[x] < b[y])
			x++;
		else
			y++;
	}
	
	return true;
}

/*
	Rule I: S(B) ≠ S(C); that is, sums of subsets cannot be equal.
*/
bool validate1(const Subset &b, const Subset &c) {
	int i, j;
	
	if(S(b) == S(c))
		return false;
	
	for(i = 1; i < b.size(); i++)
		for(j = 0; j + i < b.size(); j++)
			if(b[j] < c[j] && b[j + i] > c[j + i])
				return false;
	
	return true;
}

/*
	Rule II: If B contains more elements than C then S(B) > S(C).
*/
bool validate2(const Subset &x, const Subset &y) {
	if(x.size() > y.size())
		return (S(x) > S(y));
	else if(x.size() < y.size())
		return (S(x) < S(y));
	else
		return false;
}

void gen_subsets(Subsets &s, const Subset &x, int n, int p, int m) {
	int i;
	Subset x2;
	
	if(x.size() == m) {
		s.push_back(x);
		
		//Debug
		//draw(x);
		//cout << endl;
		
		return;
	}
	
	for(i = p; i <= n; i++) {
		x2 = x;

		x2.push_back(i);
		
		gen_subsets(s, x2, n, i + 1, m);
	}
}

vector<Subsets> gen_subsets(int n) {
	int i;
	vector<Subsets> r;
	
	for(i = 1; i <= n - 1; i++) {
		Subsets s;
		
		gen_subsets(s, {}, n, 1, i);
		
		r.push_back(s);
	}
	
	return r;
}

int total(const Subsets &a, const Subsets &b) {
	int i, j, k, r;
	bool f;
	
	//Init
	r = 0;
	f = (a[0].size() == b[0].size());
	
	for(i = 0; i < a.size(); i++)
		for(j = (f ? i : 0); j < b.size(); j++)
			if(uniek(a[i], b[j])) {
				r++;
				
				//Debug
				//draw(a[i]);
				//draw(a[j]);
				//cout << endl;
			}
	
	return r;
}

int total(const Subsets &a) {
	int i, j, k, r;
	bool f;
	
	//Init
	r = 0;
	
	for(i = 0; i < a.size(); i++)
		for(j = i; j < a.size(); j++)
			if(uniek(a[i], a[j]))
				if(!validate1(a[i], a[j])) {
					r++;
					
					//Debug
					//draw(a[i]);
					//draw(a[j]);
					//cout << endl;
				}
	
	return r;
}

int total(int n) {
	int i, j, x, r;
	vector<Subsets> s;
	
	//Init
	r = 0;
	s = gen_subsets(n);
	
	/*
	//Count all subsets
	for(i = 0; i < n - 1; i++)
		for(j = i; i + j < n - 1; j++)
			r += total(s[i], s[j]);
	*/
	
	//Count checked subsets
	for(i = 0; i < n / 2; i++)
		r += total(s[i]);
	
	return r;
}

int main() {
	cout << "Result = " << total(12) << endl;
	
	return 0;
}
