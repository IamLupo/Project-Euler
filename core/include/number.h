#include <vector>

namespace IamLupo {
	namespace Number {
		std::vector<int> toVector(long long v);
		long long toNumber(const std::vector<int> &v);
		
		long long sum(const std::vector<int> &v);
		long long nextBase(int b, int v);
	}
}