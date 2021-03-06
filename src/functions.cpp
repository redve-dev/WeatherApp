#include "../include/functions.hpp"
#include <bits/chrono.h>
#include <fstream>
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <filesystem>

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

using nlohmann::json;
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
	if(request.empty()){
		std::cerr<<"Invalid request\n";
		return json();
	}
	if(request.find(' ') != std::string::npos){
		std::cerr<<"invalid request\n";
		std::cerr<<"request contains spacebar";
		return json();
	}
	std::string data="";
	CURL* curl = curl_easy_init();
	if(curl != nullptr){
		curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	if(data.empty()){
		std::cout<<"Couldn't perform request\n";
		return json();
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
	result["timestamp"]=GetUnixTimestamp();
	return result;
}

void DumpToFile(const json& data, std::string&& filename){
	std::ofstream f;
	if (!std::filesystem::exists("data/outputs")){
		std::filesystem::create_directory("data/outputs");
	}
	f.open(filename);
	f<<data;
	f.close();
}

int GetUnixTimestamp(){
	const auto t = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(t.time_since_epoch()).count();
}
