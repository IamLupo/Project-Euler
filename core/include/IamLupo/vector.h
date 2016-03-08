#include <vector>

namespace IamLupo {
	namespace Vector {
		std::vector<int> to(long long v);
		std::vector<long long> add(const std::vector<long long> &v);
		
		bool same(std::vector<int> a, std::vector<int> b);
		
		std::vector<std::vector<int>> mirror(std::vector<std::vector<int>> v);
	}
}