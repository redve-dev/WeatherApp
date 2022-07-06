#include <string>
#include <nlohmann/json.hpp>

std::string ReadFromFile(const std::string& filename);
std::string GetRequest();
nlohmann::json PerformRequest(const std::string& request);
nlohmann::json ExtractDataFromJson(const nlohmann::json& main);
void DumpToFile(const nlohmann::json& data, std::string&& filename);
