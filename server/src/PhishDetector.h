#include <cstdlib>
#include <algorithm>
#include <regex>
#include <string>
#include <sstream>
#include <vector>

class PhishDetector
{
private:
	std::string url;
public:
	std::vector<std::string> recommend_list;
    PhishDetector(std::string url);
	int Check();
};
