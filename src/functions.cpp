#include "../lib/functions.hpp"
#include <fstream>

std::string GetAPIKey(){
	return ReadFromFile("data/APIkey");
}

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
	f>>key;
	f.close();
	return key;
}

std::string GetRequest(){
	return ReadFromFile("data/request");
}
