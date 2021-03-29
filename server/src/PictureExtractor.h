#include <string>
#include <vector>

class PictureExtractor
{
private:
	std::string url;
public:
	PictureExtractor(std::string);
	std::vector<std::string> Run();
};
