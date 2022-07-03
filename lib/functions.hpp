#include <string>
#include <iostream>
std::string GetAPIKey();
std::string ReadFromFile(const std::string& filename);
std::string GetRequest();
std::string PerformRequest(const std::string& request);
