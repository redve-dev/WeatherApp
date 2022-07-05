#include "../lib/functions.hpp"
#include <fstream>
#include <curl/curl.h>
#include <curl/easy.h>

std::string ReadFromFile(const std::string& filename){
	std::ifstream f;
	f.open(filename, std::ios::in);
	try{
		if(f.fail()){
			throw std::ifstream::failure("couldn't open a file: "+filename);
		}
	}
	catch(const std::ifstream::failure& e){
		std::cerr<<e.what()<<std::endl;
		return "";
	}
	std::string key;
	std::getline(f,key, '\n');
	f.close();
	return key;
}

std::string GetAPIKey(){
	return ReadFromFile("data/APIkey");
}

std::string GetRequest(){
	return ReadFromFile("data/request");
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string PerformRequest(const std::string& request){
	std::string json="";
	CURL* curl = curl_easy_init();
	if(curl != nullptr){
		curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &json);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return json;
}
