#include "../lib/functions.hpp"
#include <fstream>
#include <curl/curl.h>
#include <iostream>
#include <sstream>

std::string ReadFromFile(const std::string& filename){
	std::ifstream f(filename);
	if(f.fail()){
		f.close();
		std::cerr<<"couldn't open file: "<<filename<<std::endl;
		return "";
	}
	std::string key;
	std::stringstream buffer;
	buffer << f.rdbuf();
	f.close();
	return buffer.str();
}

std::string GetRequest(){
	json data = json::parse(ReadFromFile("data/input.json"));
	std::string request = data["request"];
	request.replace(request.find("{CITY}"),6,data["city"]);
	request.replace(request.find("{APIKEY}"),8,data["APIkey"]);
	return request;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

json PerformRequest(const std::string& request){
	std::string data="";
	CURL* curl = curl_easy_init();
	if(curl != nullptr){
		curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return json::parse(data);
}

json ExtractDataFromJson(const json& all){
	json result;
	auto take_from = [&](const json &from, const char *k){ result[k] = from[k]; };
	take_from(all["coord"], "lon");
	take_from(all["coord"], "lat");
	take_from(all["weather"][0], "description");
	take_from(all["main"],"temp");
	take_from(all["main"],"feels_like");
	take_from(all["main"],"pressure");
	take_from(all["main"],"humidity");
	take_from(all,"visibility");
	take_from(all["wind"],"speed");
	take_from(all["wind"],"deg");
	result["clouds_count"] = all["clouds"]["all"]; // i want change the field name

	// convert from kelvin to celsius, and round to 2 digits
	auto convert_temperatures = [&result](const char* k){
		double temp = static_cast<double>(result[k]);
		temp = (static_cast<int>((temp-273.15f)*100));
		result[k]=temp/100;
	};
	convert_temperatures("temp");
	convert_temperatures("feels_like");
	return result;
}

void DumpToFile(const json& data, std::string&& filename){
	std::ofstream f;
	f.open("data/"+filename);
	f<<data;
	f.close();
}
