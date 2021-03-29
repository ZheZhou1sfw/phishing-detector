#include "WhoIS.h"

WhoIS::WhoIS(std::string url) : url(url)
{
}

void WhoIS::Set(std::string newurl)
{
	url = newurl;
}

std::string WhoIS::Find()
{
	return "Google LLC";
}
