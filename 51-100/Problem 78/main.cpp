#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*
	Find the least value of n for which p(n) is divisible by one million.
*/

static vector<long long> pentagon;

/*
	Data:
		0, 1, 2, 5, 7, 12, 15, 22, 26, 35, 40, 51, 57, 70, 77, 92, 100,
		117, 126, 145, 155, 176, 187, 210, 222, 247, 260, 287, 301, 330,
		345, 376, 392, 425, 442, 477, 495, 532, 551, 590, 610, 651, 672,
		715, 737, 782, 805, 852, 876, 925, 950, 1001, 1027, 1080, 1107,
		1162, 1190, ...
	
	Reference:
		https://en.wikipedia.org/wiki/Pentagonal_number_theorem
		http://oeis.org/A001318
*/
vector<long long> A001318(long long max) {
	int i;
	vector<long long> r;
	
	for(i = 1; i * (3 * i + 1) / 2 <= max; i++) {
		r.push_back(i * (3 * i - 1) / 2);
		r.push_back(i * (3 * i + 1) / 2);
	}
	
	return r;
}

/*
	Data:
		1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42, 56, 77, 101, 135, 176, 231,
		297, 385, 490, 627, 792, 1002, 1255, 1575, 1958, 2436, 3010, 3718,
		4565, 5604, 6842, 8349, 10143, 12310, 14883, 17977, 21637, 26015,
		31185, 37338, 44583, 53174, 63261, 75175, 89134, 105558, 124754, ...
	
	Reference:
		https://en.wikipedia.org/wiki/Partition_%28number_theory%29
		https://oeis.org/A000041
		https://www.youtube.com/watch?v=aj4FozCSg8g
*/
int A000041(int max = 1000000) {
	int i, j;
	long long v;
	vector<long long> r;
	
	//Init
	r = {1};
	
	for(i = 1; i < max; i++) {
		v = 0;
		
		for(j = 0; j < pentagon.size() && pentagon[j] <= i; j++) {
			if(j % 4 == 0 || j % 4 == 1)
				v += r[i - pentagon[j]];
			else
				v -= r[i - pentagon[j]];
			
			v %= 1000000;
		}
		
		r.push_back(v);
		
		if(v == 0)
			return i;
	}
	
	return -1; // Nothing found
}

int main() {
	//Generate pentagon numbers
	pentagon = A001318(60000);
	
	cout << "result = " << A000041() << endl;
	
	return 0;
}
