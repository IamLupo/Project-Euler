#include <vector>

namespace IamLupo {
	typedef std::vector<long long> Primes;
	
	namespace Prime {
		bool is(const Primes &p, long long v);
		void generate(Primes &p, int l);
		
		bool isConcatenate(const IamLupo::Primes &p, const std::vector<int> &r, int v);
	}
}