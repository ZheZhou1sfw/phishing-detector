#include "PictureExtractor.h"

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

	// get the html code


	// run the regular expression with <regex> library
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

	 */

    // use this regular expression pattern (between ~):    ~(content|href|src)="https:\/\/[^"]*(logo|icon|ico)+.*png"~
    // then strip off the unnecessary parts.

    // verify: https://www.regextester.com/ use the above example and regex pattern



	return res;
}
