#include <string>

class SourceFinder
{
private:
	std::string url;
public:
	SourceFinder(std::string);
	std::string Run();
};
