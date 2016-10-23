#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>

#include "IamLupo/sqrt.h"
#include "IamLupo/math.h"

using namespace std;

/*
	Find the sum of all progressive perfect squares below one trillion (10^12).
*/

/*
	d = divider
	q = quotient
	r = remainder
	p = progression
	
	
	Conclusion A:
		Data:
			r       d       q       p       n
			1       2       4       2/1     9
			36      72      144     2/1     10404
			1225    2450    4900    2/1     12006225
			41616   83232   166464  2/1     13855173264
			25      75      225     3/1     16900
			67600   202800  608400  3/1     123383587600
			69696   104544  156816  3/2     16394241600
			3969    5292    7056    4/3     37344321
			1936    2420    3025    5/4     7322436
			1089    6534    39204   6/1     256160025
			21609   30870   44100   10/7    1361388609
			5184    5760    6400    10/9    36869184
			8       92      1058    23/2    97344
			512     1472    4232    23/8    6230016
			5832    7452    9522    23/18   70963776
			521284  658464  831744  24/19   547674002500
			12544   25872   53361   33/16   1380568336
			50625   78975   123201  39/25   9729849600
			81      360     1600    40/9    576081
			432     4392    44652   61/6    196112016
			27648   70272   178608  61/24   12551169024
			314928  355752  401868  61/54   142965659664
			50625   75600   112896  112/75  8534988225
		
		We see that the numbers on the progression is low. This gives me the
		possebilitie to bruteforce the remainder. And generate the divider, quotient and n.
		
		d = r * p
		q = d * p
		n = d * q + r
	
	Conclusion B:
		Data:
			r       d       q       p       x       n
			1       2       4       2/1     1       9
			36      72      144     2/1     36      10404
			1225    2450    4900    2/1     1225    12006225
			41616   83232   166464  2/1     41616   13855173264
			25      75      225     3/1     25      16900
			67600   202800  608400  3/1     67600   123383587600
			69696   104544  156816  3/2     34848   16394241600
			3969    5292    7056    4/3     1323    37344321
			1936    2420    3025    5/4     484     7322436
			1089    6534    39204   6/1     1089    256160025
			21609   30870   44100   10/7    3087    1361388609
			5184    5760    6400    10/9    576     36869184
			8       92      1058    23/2    4       97344
			512     1472    4232    23/8    64      6230016
			5832    7452    9522    23/18   324     70963776
			521284  658464  831744  24/19   27436   547674002500
			12544   25872   53361   33/16   784     1380568336
			50625   78975   123201  39/25   2025    9729849600
			81      360     1600    40/9    9       576081
			432     4392    44652   61/6    72      196112016
			27648   70272   178608  61/24   1152    12551169024
			314928  355752  401868  61/54   5832    142965659664
			50625   75600   112896  112/75  675     8534988225
		
		p = p1 / p2
		r = x * p2
		
		We can generate x to lower the bruteforce area.
	
	Conclusion C:
		When we watch the data in Conclusion B we see that x can be divided by p2.
		This means we can even reduce the x area.
*/

long long f(long long l) {
	long long p1, p2, d, q, r, x, n;
	vector<long long> v;
	
	//Debug
	//cout << "r	d	q	p	x	n" << endl;
	
	for(p1 = 1; p1 < 113; p1++) {
		for(p2 = 1; p2 < p1; p2++) {
			if(IamLupo::Math::gcd(p1, p2) == 1) {
				for(x = p2; x < 75000; x += p2) {
					r = x * p2;
					if((r * p1) % p2 == 0) {
						d = (r * p1) / p2;
						if((d * p1) % p2 == 0) {
							q = (d * p1) / p2;
							n = d * q + r;
							
							if(n < l && IamLupo::Sqrt::is(n)) {
								v.push_back(n);
								
								//Debug
								/*
								cout << r << "	" << d << "	" << q << "	"
									 << p1 << "/" << p2 << "	"
									 << x << "	"
									 << n
									 << endl;
								*/
							}
						}
					}
				}
			}
		}
	}
	
	return accumulate(v.begin(), v.end(), (long long)0);
}

int main() {
	//Example
	//cout << "Result = " << f(100000) << endl; // 124657
	
	//Real
	cout << "Result = " << f(1000000000000) << endl;
	
	
	return 0;
}
