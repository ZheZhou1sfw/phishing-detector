#include <string>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

class WhoIS
{
private:
	std::string url;
	Json::Value reply;
	
public:
	WhoIS(std::string);
	std::string Find();
	void Set(std::string);
};
