#include "SourceFinder.h"
#include "pdutil.h"

SourceFinder::SourceFinder(std::string url) : url(url)
{
}

std::vector<std::string> SourceFinder::Run()
{
	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	curl = curl_easy_init();
	if(curl) {
		std::string quote_url = "https://serpapi.com/search.json?engine=google_reverse_image&image_url="+url+"&api_key=bdd2fd4afa3aa9b1348835554e338885d9a4610628048fc19f893b7979a42435";
		std::cout << "DEBUG in SF " << quote_url << std::endl;
		curl_easy_setopt(curl, CURLOPT_URL, quote_url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	Json::Reader reader;
    reader.parse(readBuffer, reply);

	std::vector<std::string> res_vec;
	res_vec.clear();

	for (int i = 0; i < 7; i++)
	{
		std::string ext = reply["image_results"][i]["link"].asString();
		if (ext.length()) res_vec.push_back(ext);
		ext = reply["image_results"][i]["thumbnail_destination_url"].asString();
		if (ext.length()) res_vec.push_back(ext);
	}

	for (int i = 0; i < res_vec.size(); i++)
	{
		std::cout << "DEBUG in SF " << i << " " << res_vec[i] << std::endl;
	}
	
	return res_vec;	
}
