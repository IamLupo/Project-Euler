#include <vector>

namespace IamLupo {
	typedef std::vector<long long> Pentagonals;
	
	namespace Pentagonal {
		long long get(long long n);
		Pentagonals generate(int l);
	}
}