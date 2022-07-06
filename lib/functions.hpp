#include <string>
#include <nlohmann/json.hpp>

std::string ReadFromFile(const std::string& filename);
std::string GetRequest();
using nlohmann::json;
json PerformRequest(const std::string& request);
json ExtractDataFromJson(const json& main);
void DumpToFile(const json& data, std::string&& filename);
