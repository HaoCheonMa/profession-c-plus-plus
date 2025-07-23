#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "tools.h"
#include "cpr/cpr.h"

int main() {
	std::cout << "<REQUEST FORMAT>\n";
	std::cout << "key1 value1 key2 value2 ... method\n\n";
	while (true) {
		cpr::Url url = "http://httpbin.org/";
		std::string getRequest;
		std::vector<std::string> request;
		std::vector<cpr::Pair> params;
		cpr::Response response;
		std::cout << "Enter request: ";
		std::getline(std::cin, getRequest);


		request = strParsing(getRequest);
		if (request.size() % 2 == 0) {
			std::cerr << "\n**INPUT ERROR**\n\n";
			continue;
		}
		std::string method = request.back();
		url += method;

		for (size_t i = 0; i < request.size() - 1; i+=2)
			params.push_back({ request[i], request[i + 1]});

		if (method == "get") {
			cpr::Parameters parameters;
			for (auto& param : params)
				parameters.Add({ param.key, param.value });

			response = cpr::Get(url, parameters);
			std::cout << response.text;
		}

		else if (method == "post") {
			cpr::Payload payload(params.begin(), params.end());
			response = cpr::Post(url, payload);
			std::cout << response.text;
		}

		else {
			std::cerr << "\n**UNKNOWN METHOD**\n\n";
			continue;
		}
		std::cout << std::endl;
	}
}