#include "../lib/functions.hpp"
#include <nlohmann/json.hpp>

int main(){
	const std::string request = GetRequest();
	const json data = PerformRequest(request);
	if(data.empty()){
		std::cerr<<"Couldn't perform request\n";
		return 0;
	}
	const json result = ExtractDataFromJson(data);
	DumpToFile(result, "result.json");
	return 0;
}
