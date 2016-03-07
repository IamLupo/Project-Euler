#include "IamLupo/fibonacci.h"

long long IamLupo::Fibonacci::next(IamLupo::Fibonacci::Number &n) {
	long long t;
	
	t = n.y;
	n.y += n.x;
	n.x = t;
	
	return n.y;
}