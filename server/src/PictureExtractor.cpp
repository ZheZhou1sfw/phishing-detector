#include "PictureExtractor.h"

PictureExtractor::PictureExtractor(std::string url) : url(url)
{
}

std::vector<std::string> PictureExtractor::Run()
{
	// return extractor pictures in href
	std::vector<std::string> res;
	res.push_back("https://www.google.com/images/branding/googlelogo/1x/googlelogo_color_272x92dp.png");
	return res;
}
