#include "../lib/functions.hpp"
#include <nlohmann/json.hpp>
#include <iostream>

int main(){
	const std::string apikey = GetAPIKey();
	if(apikey.empty()){
		std::cout<<"Provide a valid openweather api key in file data/APIkey\n";
		return 1;
	}

	const std::string request = InsertDataToRequest(GetRequest(), "katowice", apikey);
	if(request.empty()){
		std::cout<<"Couldn't get a correct request from file data/request\n";
		return 1;
	}

	const json info = json::parse(PerformRequest(request));
	const json extracted_data = ExtractDataFromJson(info);
	DumpToFile(extracted_data, "result.json");
	return 0;
}
