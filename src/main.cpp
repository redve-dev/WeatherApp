#include "../lib/functions.hpp"
#include <nlohmann/json.hpp>
#include <iostream>

int main(){
	const std::string request = GetRequest();
	const json data = PerformRequest(request);
	const json result = ExtractDataFromJson(data);
	DumpToFile(result, "result.json");
	return 0;
}
