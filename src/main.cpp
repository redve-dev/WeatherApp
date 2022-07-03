#include "../lib/functions.hpp"
#include <cassert>

int main(){
	const std::string apikey = GetAPIKey();
	const std::string request = GetRequest();
	assert(!(apikey.empty() || request.empty()));
	const std::string result = PerformRequest(request+apikey);
	std::cout<<result<<std::endl;
	return 0;
}
