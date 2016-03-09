#include <vector>

namespace IamLupo {
	namespace Divider {
		typedef std::vector<int> Sum;
		
		std::vector<int> get(long long v);
		
		long long sum(long long v);
		
		Sum generate_sum(long long l);
		std::vector<int> getAbundant(long long l);
		std::vector<int> getAbundant(Sum &s);
	}
}