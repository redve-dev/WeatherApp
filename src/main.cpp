#include <curl/curl.h>
#include "../lib/functions.hpp"
#include <cassert>

int main(){
	const std::string apikey = GetAPIKey();
	assert(!apikey.empty());
	const std::string request = GetRequest();
	std::cout<<request+apikey<<std::endl;
	return 0;
}
