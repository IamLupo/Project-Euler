#include <vector>

namespace IamLupo {
	typedef std::vector<long long> Triangulars;
	
	namespace Triangular {
		long long get(long long n);
		Triangulars generate(int l);
	}
}