#include "PictureExtractor.h"
#include "pdutil.h"
#include <regex>

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
	res.push_back("https://www.google.com/images/branding/googlelogo/1x/googlelogo_color_272x92dp.png");
	
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

	exit(444);

	return res;
}
