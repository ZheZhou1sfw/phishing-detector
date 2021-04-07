#include <string>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <vector>

class SourceFinder
{
private:
	std::string url;
	Json::Value reply;
public:
	SourceFinder(std::string);
	std::vector<std::string> Run();
};
