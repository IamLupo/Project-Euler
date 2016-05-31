#include <iostream>
#include <set>
#include <vector>

using namespace std;

int const L = 12000;

// You don't need this much, but I didn't want to think how much you need
vector<int> best(12100, 999999999);

int product; // Using global variables is ugly but convenient

void generate(int n, int k, int s, int num) {
	int quotient;
	
	for(;k * k <= n; k++) {
		if(!(n % k)) {
			quotient = n / k;
			
			if(best[product - s - k - quotient + num + 2] > product)
				best[product - s - k - quotient + num + 2] = product;
			
			if(k * k <= quotient)
				generate(quotient, k, s + k, num + 1);
		}
	}
}

int main(){
	int i, sum;
	set<int> s;
	set<int>::const_iterator it;
	
	//Init
	sum = 0;
	
	for(product = 4; product <= 12100; product++)
		generate(product, 2, 0, 0);
	
	for(i = 2; i <= L; i++)
		s.insert(best[i]);
	
	for(it = s.begin(); it != s.end(); it++)
		sum += *it;
	
	cout << "Result = " << sum << endl;
}