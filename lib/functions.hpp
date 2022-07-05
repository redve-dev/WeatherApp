#include <string>
#include <iostream>
std::string GetAPIKey();
std::string ReadFromFile(const std::string& filename);
std::string GetRequest();
std::string PerformRequest(const std::string& request);
std::string InsertDataToRequest(std::string request, const std::string& city, const std::string& key);
