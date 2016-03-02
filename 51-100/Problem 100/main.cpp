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
	By finding the first arrangement to contain over 10^12 = 1,000,000,000,000 discs in total,
	determine the number of blue discs that the box would contain.
*/

/*
	Data:
		First generation:
			21 coloured (15 blue and 6 red)
			P(BB) = (15/21)×(14/20) = (15 * 14)/(21 * 20) = 210/420 = 1/2
		
		Second generation:
			120 coloured (85 blue and 35 red)
			P(BB) = (85/120)×(84/119) = (85 * 84)/(120 * 119) = 7140/14280 = 1/2
		
		Question:
			1,000,000,000,000 <= coloured (? blue and ? red)
	
	Generated data:
		n				blue			red
		21				15				6
		120     		85				35
		697     		493				204
		4060    		2871			1189
		23661   		16731			6930
		137904  		97513			40391
		803761  		568345			235416
		4684660 		3312555			1372105
		27304197        19306983		7997214
		159140520       112529341		46611179
		927538921       655869061		271669860
		5406093004      3822685023		1583407981
		31509019101     22280241075		9228778026
		183648021600    129858761425	53789260175
		1070379110497   756872327473	313506783024
	
	Conclusion:
		Init:
			n = 21
			blue = 15
			red = 6
			
		Next:
			n = (3 * n) + (4 * b) - 3
			blue = (2 * n) + (3 * b) - 2
			red = n - blue
*/

long long f(long long v) {
	long long b, n, t;
	
	//Init
	b = 15;
	n = 21;
	
	while(n < v) {
		t = (2 * n) + (3 * b) - 2;
		n = (3 * n) + (4 * b) - 3;
		b = t;
	}
	
	return b;
}

int main() {
	cout << "result = " << f(1000000000000) << endl;
	
	return 0;
}
