#include "../lib/functions.hpp"
#include <fstream>

std::string GetAPIKey(){

	std::ifstream f;
	try{
		f.open("APIkey", std::ios::in);
		if(f.fail()){
			throw std::ifstream::failure("couldn't open a file with apikey");
		}
	}
	catch(const std::ifstream::failure & e){
		std::cerr<<e.what()<<std::endl;
		f.close();
		return "";
	}
	std::string key;
	f>>key;
	f.close();
	return key;
}
