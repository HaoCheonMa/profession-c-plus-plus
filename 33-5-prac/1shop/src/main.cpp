#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <exception>
#include "tools.h"

std::vector<std::string> inputRequest(const std::string& label) {
	std::string data;
	while (data.empty()) {
		std::cout << label;
		getline(std::cin, data);
	}
	std::vector<std::string> request = strParsing(data);
	return request;
}

class Shop {
	static std::map<long, short int> storage;
	static std::map<long, short int> cart;

	static void add(long inArticle, short int inAmount) {
		auto itArticle = storage.find(inArticle);
		if (itArticle == storage.end()) {
			throw std::invalid_argument("Article not found in storage");
		}
		if (inAmount <= 0) {
			throw std::invalid_argument("Amount must be positive");
		}
		if (itArticle->second == 0) {
			throw std::runtime_error("Article ended");
		}
		if (itArticle->second < inAmount) {
			throw std::runtime_error("Not enough items in storage");
		}

		itArticle->second -= inAmount;
		cart[inArticle] += inAmount;

		std::cout << "Article " << inArticle << " successfully added in amount " << inAmount << "\n";
	}

	static void remove(long inArticle, short int inAmount) {
		auto itCart = cart.find(inArticle);
		if (itCart == cart.end())
			throw std::invalid_argument("Article not found in cart");
		if (inAmount <= 0)
			throw std::invalid_argument("Amount must be positive");
		if (itCart->second < inAmount)
			throw std::runtime_error("Not enough items in cart");

		itCart->second -= inAmount;
		storage[inArticle] += inAmount;
		std::cout << "Article " << inArticle << " successfully removed in amount " << inAmount << "\n";

		if (itCart->second == 0)
			cart.erase(itCart);
	}

	static void printStorage(bool& complete) {
		std::cout << "--- Storage contents ---\n";
		if (storage.empty()) {
			std::cout << "(empty)\n";
			complete = true;
			return;
		}
		for (const auto& item : storage) {
			std::cout << "Article: " << item.first << " | Amount: " << item.second << '\n';
		}
		complete = true;
	}

	static void printCart(bool& complete) {
		std::cout << "--- Cart contents ---\n";
		if (cart.empty()) {
			std::cout << "(empty)\n";
			complete = true;
			return;
		}
		for (const auto& item : cart) {
			std::cout << "Article: " << item.first << " | Amount: " << item.second << '\n';
		}
		complete = true;
	}

	static int safeStoi(const std::string& s) {
		try {
			return std::stoi(s);
		}
		catch (const std::invalid_argument&) {
			throw std::invalid_argument("converting error");
		}
		catch (const std::out_of_range&) {
			throw std::invalid_argument("converting error");
		}
	}

	static long safeStol(const std::string& s) {
		try {
			return std::stol(s);
		}
		catch (const std::invalid_argument&) {
			throw std::invalid_argument("converting error");
		}
		catch (const std::out_of_range&) {
			throw std::invalid_argument("converting error");
		}
	}

public:	

	static void fillStorage() {
		while (true) {
			std::vector<std::string> request = inputRequest("Enter article and amount: ");
			if (request[0] == "stop")
				return;
			if (request.size() >= 2) {
				try {
					if (safeStol(request[0]) < 1)
						throw std::invalid_argument("Invalid article\n");
					if (safeStoi(request[1]) < 0)
						throw std::invalid_argument("Invalid amount\n");
					auto itArticle = storage.find(safeStol(request[0]));
					if (itArticle == storage.end())
						storage.insert(std::make_pair(std::stol(request[0]), safeStoi(request[1]) < 0));
					else
						std::cerr << "Article already in storage\n";
				}
				catch (std::invalid_argument& e) {
					std::cout << "Error: " << e.what() << std::endl;
				}
			}
			else
				std::cout << "Not enough data\n";
		}
	}

	static void shopping() {
		long inArticle = 0;
		short int inAmount = 0;
		while (true) {
			bool basicCmd = false;
			std::vector<std::string> request = inputRequest("Enter promt or just cmd(cmd article amount): ");
			if (request[0] == "stop")
				return;

			else if (request[0] == "storage")
				printStorage(basicCmd);

			else if (request[0] == "cart")
				printCart(basicCmd);

			if (basicCmd == false) {
				try {
					inArticle = safeStol(request[1]);
					inAmount = safeStoi(request[2]);
					if (request[0] == "add")
						add(inArticle, inAmount);
					else if (request[0] == "remove")
						remove(inArticle, inAmount);
					else
						std::cerr << "Unknown command\n";
				}
				catch (const std::invalid_argument& e) {
					std::cerr << "Invalid argument: " << e.what() << '\n';
				}
				catch (const std::runtime_error& e) {
					std::cerr << "Runtime error: " << e.what() << '\n';
				}
				catch (...) {
					std::cerr << "Unknown error occurred\n";
				}
			}
		}

	}

};

std::map<long, short int> Shop::storage;
std::map<long, short int> Shop::cart;

int main() {
	std::cout << "**Enter 'stop' to end**\n\n";
	std::cout << "<Filling storage>\n\n";
	Shop::fillStorage();
	std::cout << "\n";
	std::cout << "<Shopping>\n\n";
	std::cout << "**CMDs: add, remove, (just cmd)storage, (just cmd)cart**\n\n";
	Shop::shopping();
}