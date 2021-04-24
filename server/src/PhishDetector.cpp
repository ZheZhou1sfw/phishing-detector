#include "PhishDetector.h"
#include "PhishDatabase.h"
#include "PictureExtractor.h"
#include "SourceFinder.h"
#include "WhoIS.h"
#include "Share.h"
#include <vector>
#include <map>
#include <iostream>

PhishDetector::PhishDetector(std::string url) : url(url)
{
	recommend_list.clear();
}

#define RESERVED_SUF_SIZE 12
std::string reserved_suf[RESERVED_SUF_SIZE] = {"com", "cn", "org", "pt", "sa", "co", "uk", "pe", "edu", "net", "gov", "pl"};

std::string url_root_finder(std::string url)
{
	std::string url_root = "";
	int check = 0;
	int i;
	for (i = 0; i < url.length(); i++)
	{
		if (url[i] == '/') check++;
		if (check == 3) break;
	}
	std::string temp = "";
	check = 0;
	for (i--; i >= 0; i--)
	{
		if (url[i] == '.' || url[i] == '/')
		{
			bool mark = 0;
			for (int i = 0; i < RESERVED_SUF_SIZE; i++)
				if (reserved_suf[i] == temp)
				{					
					mark = 1;
					break;
				}
			if (mark)
			{
				url_root = "." + temp + url_root;
				temp = "";
				continue;
			}
			else
			{
				url_root = temp + url_root;
				break;
			}
		}
		temp = url[i] + temp;
	}
	return url_root;
}

int PhishDetector::Check()
{
	PhishDatabase phish_db;
	int pd_check = phish_db.Check(url);
	if (pd_check == 2)
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
			std::vector<std::string> sf_run = sf.Run();
			for (int i = 0; i < sf_run.size(); i++) source_v.push_back(sf_run[i]);
		}

		for (int i = 0; i < source_v.size(); i++)
			std::cout << source_v[i] << std::endl; // debug

		WhoIS wi(url_root_finder(url));

		std::string input_owner = wi.Find();

		bool empty_mark = 0;
		if (input_owner == "")
			empty_mark = 1;

		std::map<std::string, bool> mark;
		
		int eq_cnt = 0;
		for (int i = 0; i < source_v.size(); i++)
		{
			std::string url_root = url_root_finder(source_v[i]);
			if (mark[url_root] == 0)
			{
				mark[url_root] = 1;
				if (!empty_mark)
				{
					wi.Set(url_root);
					eq_cnt += wi.Find() == input_owner ? 1 : 0;
				}
				else
				{
					recommend_list.push_back(url_root);
				}
			}
		}

		std::cout << "eq_cnt = " << eq_cnt << std::endl; // debug

		if (eq_cnt) return 3;	   
		
		return 2;

		// bigger eq_cnt, more chance that it's not a phishing website
	}
	else if (pd_check == 1)
	{
		std::cout << "Not Phishing according to Phishtank" << std::endl;
		return 1;
	}
	else if (pd_check == 0)
	{
		std::cout << "Is Phishing according to Phishtank" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Error: phishtank result's wrong" << std::endl;
		return -1;
	}
	return 1;
}
