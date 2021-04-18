#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include "PhishDetector.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "crow_all.h"
#include <map>

using namespace std;

int main()
{

	// testing for crow

	/*
	crow::SimpleApp app;

	CROW_ROUTE(app, "/phishdetector")
		.methods("GET"_method)
		([](const crow::request& req){
			 std::string URL = req.url_params.get("url");
			 if (URL == "") return crow::response(400);
			 PhishDetector pd(URL);
			 int pdc = pd.Check();
			 if (pdc == -1) return crow::response(400);
			 std::ostringstream os;
			 os << pdc;
			 return crow::response{os.str()};
		 });	
	app.port(44444).run();

	return 0;
	*/
	
	
	int choice;
	cin >> choice;

	if (choice)
	{
		cout << "=== PD server starting ===" << endl;
		// socket
		int listenfd = socket(AF_INET, SOCK_STREAM, 0);
		if (listenfd == -1)
		{
			cout << "Error: can't set up socket" << endl;
			return -1;
		}
		// bind
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(44444);
		addr.sin_addr.s_addr = INADDR_ANY;
		if (bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
			std::cout << "Error: can't bind" << std::endl;
			return -1;
		}
		// listen
		if(listen(listenfd, 5) == -1) {
			std::cout << "Error: can't listen" << std::endl;
			return 0;
		}
		// accept
		int conn;
		char clientIP[INET_ADDRSTRLEN] = "";
		struct sockaddr_in clientAddr;
		socklen_t clientAddrLen = sizeof(clientAddr);
		while (true) {
			std::cout << "...listening" << std::endl;
			conn = accept(listenfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
			if (conn < 0) {
				std::cout << "Error: can't accept" << std::endl;
				continue;
			}
			inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
			std::cout << "...connect " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;

			char buf[255];
			while (true) {
				memset(buf, 0, sizeof(buf));
				int len = recv(conn, buf, sizeof(buf), 0);
				buf[len] = '\0';
				if (strcmp(buf, "exit") == 0) {
					std::cout << "...disconnect " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;
					break;
				}
				std::cout << buf << std::endl;
				string URL = string(buf);
				cout << "DEBUG = " << URL << endl;
				PhishDetector pd(URL);
				cout << pd.Check() << endl;
				send(conn, "True", 4, 0);
			}
        
			close(conn);
		}
		close(listenfd);
	}
	else
	{
		string URL;
		cin >> URL;
		PhishDetector pd(URL);
		cout << pd.Check() << endl;
	}
	return 0;
}
