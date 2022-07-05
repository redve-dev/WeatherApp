#include "../lib/functions.hpp"
#include <cassert>
#include <algorithm>

int main(){
	const std::string apikey = GetAPIKey();
	assert(!apikey.empty());
	const std::string request = InsertDataToRequest(GetRequest(), "katowice", apikey);
	assert(!request.empty());
	std::string result = PerformRequest(request);
	std::replace(result.begin(), result.end(), ' ', '_');
	std::cout<<result;
	return 0;
}
