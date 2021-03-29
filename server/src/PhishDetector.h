#include <cstdlib>
#include <algorithm>
#include <regex>
#include <string>
#include <sstream>

class PhishDetector
{
private:
	std::string url;
public:
    PhishDetector(std::string url);
	bool Check();
};
