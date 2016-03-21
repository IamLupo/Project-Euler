#include <set>

namespace IamLupo {
	typedef std::set<long long> Triangulars;
	
	namespace Triangular {
		bool is(long long n);
		long long get(long long n);
		Triangulars generate(int l);
	}
}