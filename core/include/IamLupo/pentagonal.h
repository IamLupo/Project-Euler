#include <vector>

namespace IamLupo {
	typedef std::vector<long long> Pentagonals;
	
	namespace Pentagonal {
		bool is(long long n);
		long long get(long long n);
		Pentagonals generate(int l);
	}
}