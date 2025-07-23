#include <iostream>
#include <string>
#include "tools.h"
#include "cpr/cpr.h"



int main() {
	std::cout << "<REQUESTS>\n";
	std::cout << "get\npost\nput\ndelete\npatch\nexit\n\n";
	std::string request;
	cpr::Response response;
	while (true) {
		std::string url = "http://httpbin.org/";
		request = input("Enter request: ");
		if (request == "get")
			response = cpr::Get(cpr::Url(url + request));

		else if (request == "post")
			response = cpr::Post(cpr::Url(url + request));

		else if (request == "put") 
			response = cpr::Put(cpr::Url(url + request));

		else if (request == "delete") 
			response = cpr::Delete(cpr::Url(url + request));

		else if (request == "patch") 
			response = cpr::Patch(cpr::Url(url + request));

		else if (request == "exit")
			break;

		else
			std::cerr << "\n**UNKNOWN COMMAND**\n";

		std::cout << request << ": " << response.text;

		std::cout << std::endl;
	}

	std::cout << "\n<PROGRAMM STOPPED>\n";
}