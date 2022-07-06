#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
std::string GetAPIKey();
std::string ReadFromFile(const std::string& filename);
std::string GetRequest();
std::string PerformRequest(const std::string& request);
std::string InsertDataToRequest(std::string request, const std::string& city, const std::string& key);
using nlohmann::json;
json ExtractDataFromJson(const json& main);
