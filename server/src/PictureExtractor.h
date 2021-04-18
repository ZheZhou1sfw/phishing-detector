#include <string>
#include <vector>
#include <iostream>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

class PictureExtractor
{
private:
	std::string url;
public:
	PictureExtractor(std::string);
	std::vector<std::string> Run();
};
