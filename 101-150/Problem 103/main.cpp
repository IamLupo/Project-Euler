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
	Given that A is an optimum special sum set for n = 7, find its set string.
*/

/*
	https://en.wikipedia.org/wiki/Subset_sum_problem
	
	Data:
		f(1): {1}							S(A) = 1
		f(2): {1,  2}						S(A) = 3
		f(3): {2,  3,  4}					S(A) = 9
		f(4): {3,  5,  6,  7}				S(A) = 21
		f(5): {6,  9,  11, 12, 13}			S(A) = 51
		f(6): {11, 18, 19, 20, 22, 25}		S(A) = 115
		f(7): {20, 31, 38, 39, 40, 42, 45}	S(A) = 255
	
		f_wrong(6): {11, 17, 20, 22, 23, 24}	S(A) = 117
		
	Expectation:
		A = {a1, a2, ... , an}
		B = {b, a1+b, a2+b, ... ,an+b}
		where b is the "middle" element on the previous row.
		
		f(6):
			is not {11, 17, 20, 22, 23, 24}		S(A) = 117
			is     {11, 18, 19, 20, 22, 25}		S(A) = 115
	
	Conclusion:
		distance(f(2)) = {1}
		distance(f(3)) = {1, 1}
		distance(f(4)) = {2, 1, 1}
		distance(f(5)) = {3, 2, 1, 1}
		distance(f(6)) = {7, 1, 1, 2, 3}
		
		distance(f(6)) = {sum(distance(f(5))), mirror(distance(f(5)))}
*/

/*
	Sum set
*/
int S(const vector<int> &v) {
	return accumulate(v.begin(), v.end(), 0);
}

/*
	Generate distance between numbers
	
	Example:
		f({3, 4, 6, 9}) = {1, 2, 3}
*/
vector<int> distance(const vector<int> &v) {
	int i;
	vector<int> r;
	
	for(i = 1; i < v.size(); i++)
		r.push_back(v[i] - v[i - 1]);
	
	return r;
}

vector<int> next(const vector<int> &v) {
	int i, l;
	vector<int> d, o1, o2;
	
	//Init
	l = v.size() / 2;
	d = distance(v);
	
	//Generate Option 1
	o1.push_back(v[l]);
	for(i = 0; i < v.size(); i++)
		o1.push_back(v[i] + v[l]);
	
	if(v.size() == 1)
		return o1;
	
	//Generate Option 2
	reverse(d.begin(), d.end());
	
	o2.push_back(v[l]);
	o2.push_back(v[l] + accumulate(d.begin(), d.end(), 0));
	for(i = 0; i < d.size(); i++)
		o2.push_back(o2[1 + i] + d[i]);
	
	//Check results
	if(S(o1) <= S(o2))
		return o1;
	else
		return o2;
}

string toString(const vector<int> &v) {
	int i;
	string r;
	
	for(i = 0; i < v.size(); i++)
		r += to_string(v[i]);
	
	return r;
}

/*
	Extra check if generated answer fits the rules
*/
bool check(const vector<int> &v) {
	int i, j, t;
	vector<int> l = v;
	
	for(i = 0; i < v.size(); i++) {
		for(j = i + 1; j < v.size(); j++) {
			t = v[i] + v[j];
			
			cout << t << endl;
			
			if(find(l.begin(), l.end(), t) != l.end())
				return false;
			
			l.push_back(t);
		}
	}
	
	return true;
}

string f(int l) {
	int i;
	vector<int> v = {1};
	
	//cout << "f(1) = " << toString(v) << endl;
	for(i = 1; i < l; i++) {
		v = next(v);
		//cout << "f(" << to_string(i + 1) << ") = " << toString(v) << endl;
	}
	
	return toString(v);
}

int main() {
	cout << "Result = " << f(7) << endl;
	
	return 0;
}
