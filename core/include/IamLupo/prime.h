#include <vector>

namespace IamLupo {
	typedef std::vector<long long> Primes;
	
	namespace Prime {
		bool is(const Primes &p, long long v);
		Primes generate(int l);
		Primes readFile(int l);
		
		bool isConcatenate(const Primes &p, const std::vector<int> &r, int v);
	}
}