#include <iostream>
#include <string>
#include "tools.h"
#include "cpr/cpr.h"

int main() {
	cpr::Url url = "http://httpbin.org/html";
	cpr::Response response = cpr::Get(url, cpr::Header({{"Accept", "text/html"}}));

	unsigned start = response.text.find("<h1>");
	unsigned end = response.text.find("</h1>");

	std::string header = response.text.substr(start + 4, end - (start + 4));
	std::cout << header;
}