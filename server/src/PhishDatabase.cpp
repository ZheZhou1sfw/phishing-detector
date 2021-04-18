#include "PhishDatabase.h"
#include "pdutil.h"

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

PhishDatabase::PhishDatabase()
{
}

int PhishDatabase::Check(std::string url)
{
	// if url is in, return blablabla (positive/negative/possibility)

	// system("curl --user-agent 'Chrome/79' -X POST https://checkurl.phishtank.com/checkurl/ -F 'format=json' -F 'url=https://www.google.com'");

	// std::string exec_str = "curl --user-agent 'Chrome/79' -X POST https://checkurl.phishtank.com/checkurl/ -F 'format=json' -F 'url="+url+"'";
	// std::string readBuffer = exec(exec_str.c_str());

	// std::cout << readBuffer << std::endl;

	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	curl = curl_easy_init();
	if(curl) {
		std::string quote_url = "https://checkurl.phishtank.com/checkurl/";
		std::string post_cmd = "&format=json&url="+url;
		std::cout << "DEBUG in SF " << quote_url << std::endl;
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_cmd.c_str());
		curl_easy_setopt(curl, CURLOPT_URL, quote_url.c_str());
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Chrome/79");		
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}	

	std::cout << readBuffer << std::endl;
	
	Json::Reader reader;
    reader.parse(readBuffer, reply); 
	
	std::string in_database = reply["results"]["in_database"].asString();
	std::string verified = reply["results"]["verified"].asString();

	if (in_database != "true") return 2;
	if (verified == "true") return 1;
	else return 0;
	return -1;
}
