#include "WhoIS.h"
#include "pdutil.h"

WhoIS::WhoIS(std::string url) : url(url)
{
}

void WhoIS::Set(std::string newurl)
{
	url = newurl;
}

std::string WhoIS::Find()
{
	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	curl = curl_easy_init();
	if(curl) {
		std::string quote_url = "https://api.whoishippo.com/v1/vpeaiil8n1x420059r5lw1mwsn7eiqpz/"+url;
		std::cout << "DEBUG " << quote_url << std::endl;
		curl_easy_setopt(curl, CURLOPT_URL, quote_url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	if (readBuffer[0] != '{') return ""; // not a json reply
	Json::Reader reader;
    if (reader.parse(readBuffer, reply))
	{
		std::cout << "DEBUG " << reply["whoisServerRecord"]["adminContact"]["organization"].asString() << std::endl;
		return reply["whoisServerRecord"]["adminContact"]["organization"].asString();
	}
	else
		return "";
}
