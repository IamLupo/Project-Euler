#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;

/*
	Find the sum of all numbers, less than one million,
	which are palindromic in base 10 and base 2.
*/

static vector<int> result;

int convBase2to10(vector<int> &v) {
	int i, r;
	
	r = 0;
	
	for(i = 0; i < v.size(); i++) {
		r += pow(2, i) * v[i];
	}
	
	return r;
}

void reflect(vector<int> &v) {
	int i;
	
	for(i = v.size(); i > 0; i--) {
		v.push_back(v[i - 1]);
	}
}

void reflect2(vector<int> &v, int value) {
	int i;
	
	v.push_back(value);
	
	for(i = v.size() - 1; i > 0; i--) {
		v.push_back(v[i - 1]);
	}
}

bool isReflection(int v) {
	int i;
	vector<int> v2;
	
	for(i = v; i != 0; i /= 10) {
		v2.push_back(i % 10);
	}
	
	for(i = 0; i < (v2.size() / 2); i++)
		if(v2[i] != v2[v2.size() - 1- i])
			return false;
	
	return true;
}

void bruteforce(vector<int> &v, int level, int max) {
	if(level == max) {
		int i, r, r2;
		vector<int> v2, v3;
		vector<int>::iterator it;
		
		v2 = v;
		reflect(v2);
		r = convBase2to10(v2);
		it = find(result.begin(), result.end(), r);
		
		if(isReflection(r) && it == result.end() && r < 1000000 && v2[0] != 0) {
			cout << r << "	> ";
			
			for(i = 0; i < v2.size(); i++)
				cout << v2[i];
			cout << endl;
			
			result.push_back(r);
		}
		
		v2 = v;
		reflect2(v2, 0);
		r = convBase2to10(v2);
		it = find(result.begin(), result.end(), r);
		
		if(isReflection(r) && it == result.end() && r < 1000000 && v2[0] != 0) {
			cout << r << "	> ";
			
			for(i = 0; i < v2.size(); i++)
				cout << v2[i];
			cout << endl;
			
			result.push_back(r);
		}
		
		v2 = v;
		reflect2(v2, 1);
		r = convBase2to10(v2);
		it = find(result.begin(), result.end(), r);
		
		if(isReflection(r) && it == result.end() && r < 1000000 && v2[0] != 0) {
			cout << r << "	> ";
			
			for(i = 0; i < v2.size(); i++)
				cout << v2[i];
			cout << endl;
			
			result.push_back(r);
		}
		
		return;
	}
	
	v.push_back(1);
	bruteforce(v, level + 1, max);
	v.pop_back();
	
	v.push_back(0);
	bruteforce(v, level + 1, max);
	v.pop_back();
}

long sumPalindromic() {
	int i;
	vector<int> v;
	
	result.clear();
	result.push_back(1);
	
	for(i = 1; i <= 10; i++)
		bruteforce(v, 0, i);
	
	return accumulate(result.begin(), result.end(), 0);
}

int main() {
	cout << "result = " << sumPalindromic() << endl;
		
	return 0;
}