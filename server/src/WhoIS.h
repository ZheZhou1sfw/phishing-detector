#include <string>

class WhoIS
{
private:
	std::string url;
public:
	WhoIS(std::string);
	std::string Find();
	void Set(std::string);
};
