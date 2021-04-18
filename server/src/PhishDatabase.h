#include <string>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

class PhishDatabase
{
private:
	Json::Value reply;

public:
	PhishDatabase();
	int Check(std::string);
};
