#include "../lib/functions.hpp"
#include <cassert>

int main(){
	const std::string apikey = GetAPIKey();
	assert(!apikey.empty());
	if(apikey.empty()){
		std::cout<<"Provide a valid openweather api key in file data/APIkey\n";
		return 1;
	}
	const std::string request = InsertDataToRequest(GetRequest(), "katowice", apikey);
	if(request.empty()){
		std::cout<<"Couldn't get a correct request from file data/request\n";
		return 1;
	}
	const std::string result = PerformRequest(request);
	std::cout<<result;
	return 0;
}
