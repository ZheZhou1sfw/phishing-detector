#include "PhishDetector.h"
#include "PhishDatabase.h"
#include "PictureExtractor.h"
#include "SourceFinder.h"
#include "WhoIS.h"
#include <vector>
#include <iostream>

PhishDetector::PhishDetector(std::string url) : url(url)
{
}

bool PhishDetector::Check()
{
	PhishDatabase phish_db;
	if (phish_db.Check(url) == 2)
	{
		// url is not in DB yet, need to self-check
		PictureExtractor pic_ext(url);
		std::vector<std::string> picture_v = pic_ext.Run();
		std::vector<std::string> source_v;
		
		std::cout << picture_v[0] << std::endl; // debug

		// find source of each photo using picture search API(Google, for example)
		for (int i = 0; i < picture_v.size(); i++)
		{
			SourceFinder sf(picture_v[i]);
			source_v.push_back(sf.Run());
		}

		std::cout << source_v[0] << std::endl; // debug

		WhoIS wi(url);

		std::string input_owner = wi.Find();

		std::cout << input_owner << std::endl; // debug
		
		int eq_cnt = 0;
		for (int i = 0; i < source_v.size(); i++)
		{
			wi.Set(source_v[i]);
			eq_cnt += wi.Find() == input_owner ? 1 : 0;
		}

		std::cout << "eq_cnt = " << eq_cnt << std::endl; // debug

		// bigger eq_cnt, more chance that it's not a phishing website
		
		return 0;
	}
	return 1;
}