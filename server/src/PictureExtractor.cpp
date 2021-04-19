#include "PictureExtractor.h"
#include "pdutil.h"
#include <regex>

using namespace std;

PictureExtractor::PictureExtractor(std::string url) : url(url)
{
}

//std::vector<std::string> PictureExtractor::Run()
//{
//	// return extractor pictures in href
//	std::vector<std::string> res;
//	res.push_back("https://www.google.com/images/branding/googlelogo/1x/googlelogo_color_272x92dp.png");
//	return res;
//}

std::vector<std::string> PictureExtractor::Run()
{
	// return extractor pictures in href
	std::vector<std::string> res;

	// tmp
	// res.push_back("https://www.google.com/images/branding/googlelogo/1x/googlelogo_color_272x92dp.png");
	
	// TODO step1: get the html code
	CURL *curl;
	CURLcode res_curl;
	std::string readBuffer;
	curl = curl_easy_init ();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);		
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Chrome/79");		
		res_curl = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	// std::cout << readBuffer << std::endl;

	// TODO step2: run the regular expression with <regex> library
	// example urls for testing:
	/*
        content="https://static.slickdealscdn.com/images/sd_share_logo.png"
        content="https://static.slickdealscdn.com/images/sd_share_logo.png?8557"
        content="https://www.facebook.com/images/fb_icon_325x325.png"
        content="https://abs.twimg.com/responsive-web/client-web/icon-ios.b1fc7275.png"
        content="https://www.pinterest.com/"
        content="https://s.pinimg.com/webapp/logo_trans_144x144-5e37c0c6.png"
        content="https://what_icoasfcc.png"
        src="https://abs.twimg.com/errors/logo46x38.png"


        需要补全的：
        src="/logos/doodles/2021/celebrating-laura-bassi-6753651837109199-l.png"
	 */

    // use this regular expression pattern (between ~):
    // 完整url pattern:   ~(content|href|src)="https:\/\/[^"]*(logo|icon|ico)+.*png"~
    // 完整url pattern:   ~(content|href|src)="http:\/\/[^"]*(logo|icon|ico)+.*png"~
    // 需要补全的url pattern:     ~(content|href|src)="\/[^"]*(logo|icon|ico)+.*png"~

    // then strip off the unnecessary parts in urls.

    // verify: https://www.regextester.com/ use the above example and regex pattern

	// cout << readBuffer << endl;
	// exit(123);

	// regex_search(readBuffer, result, pattern);
	// for (auto x : result)
	// 	cout << x << endl;

	string::const_iterator iterStart;
	string::const_iterator iterEnd;
	std::string temp;

	std::smatch result1;
	std::regex pattern1("https://[^\"\'\(]*(logo|icon|ico)+.*?png");
	iterStart = readBuffer.begin();
	iterEnd = readBuffer.end();	
	while (regex_search(iterStart, iterEnd, result1, pattern1))
	{
		temp = result1[0];
		// std::cout << temp << std::endl;
		res.push_back(temp);
		iterStart = result1[0].second;
	}

	std::smatch result2;
	std::regex pattern2("http://[^\"\'\(]*(logo|icon|ico)+.*?png");
	iterStart = readBuffer.begin();
	iterEnd = readBuffer.end();	
	while (regex_search(iterStart, iterEnd, result2, pattern2))
	{
		temp = result2[0];
		// std::cout << temp << std::endl;
		res.push_back(temp);
		iterStart = result2[0].second;
	}

	std::smatch result3;
	std::regex pattern3("/[^\"\'\(]*(logo|icon|ico)+.*?png");
	iterStart = readBuffer.begin();
	iterEnd = readBuffer.end();	
	while (regex_search(iterStart, iterEnd, result3, pattern3))
	{
		temp = result3[0];
		if (temp[1] != '/')
			res.push_back(url+temp);
		iterStart = result3[0].second;
	}
   
	for (int i = 0; i < res.size(); i++)
		std::cout << i << ' ' << res[i] << std::endl;

	return res;
}
