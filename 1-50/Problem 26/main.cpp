#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
	Find the value of d < 1000 for which 1/d contains the longest
	recurring cycle in its decimal fraction part.
*/

int checkCycle(vector<int> &e) {
	int i, j, z, d, r;
	bool f;
	
	if(e.size() >= 10000) {
		for(i = 0; i < 10; i++) {
			for(j = i + 2; j * 3 < e.size(); j++) {
				if(e[i] == e[j]) {
					f = true;
					d = j - i;
					r = 0;
					
					for(z = i; z < j + d; z++) {
						if(e[z] != e[z + d])
							f = false;
						else
							r++;
					}
					
					if(f)
						return r;
				}
			}
		}
	}
	
	return -1;
}

int getCycle(int v) {
	int l, m, r, t, i;
	vector<int> e;
	
	if(v == 1)
		return 1;
	
	//Init
	l = (v < 10) ? 10 : (v < 100) ? 100 : 1000;
	m = l % v;
	t = (l / v);
	r = 0;
	
	for(i = l / 10; i > 0; i /= 10) {
		e.push_back(t / i);
		t %= 10;
	}
	
	//Next decimal
	while(m != 0) {
		m *= l;
		t = (m / v);
		m %= v;
		
		for(i = l / 10; i > 0; i /= 10) {
			e.push_back(t / i);
			t %= 10;
		}
		
		r = checkCycle(e);
		if(r != -1)
			break;
		r = 0;
	}
	
	if(m == 0)
		r = e.size();
	
	return r;
}

int findLongestCycle(int m) {
	int i, t, r, p;
	
	r = 0;
	
	for(i = 1; i < m; i++) {
		t = getCycle(i);
		
		//Debug
		//cout << i << " > " << t << endl;
		
		if(t > r) {
			r = t;
			p = i;
		}
	}
	
	return p;
}

int main() {
	cout << "result = " << findLongestCycle(1000) << endl;
		
	return 0;
}