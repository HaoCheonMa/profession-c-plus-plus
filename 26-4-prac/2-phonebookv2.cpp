#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <limits>

class Note {
	std::string notePhone;
	std::string noteName;
public:
	void setNote(std::string& phone, std::string& name) {
		notePhone = phone;
		noteName = name;
	}

	const std::string& getPhone(){
		return notePhone;
	}

	const std::string& getName() {
		return noteName;
	}
};

class PhoneBook {
	static std::map<std::string, std::string> byNumber;
	static std::multimap<std::string, std::string> byName;
public:
	static void addNote(Note* notes) {
		byNumber.insert({ notes->getPhone(), notes->getName() });
		byName.insert({ notes->getName(), notes->getPhone() });
	}

	static const std::map<std::string, std::string>& getByNumber(){
		return byNumber;
	}
	static const std::multimap<std::string, std::string>& getByName() {
		return byName;
	}
};

bool requestParser(std::string& request) {
	std::istringstream ssReq(request);
	std::string nameSymUp = "ABCDEFGHIJKLMNOPQRSTYVWXYZ";
	std::string nameSymLow = "abcdefghijklmnopqrstyvwxyz";
	std::string phoneSym = "+1234567890";
	std::string phone;
	ssReq >> phone;
	if (phone.length() != 12 || phone.substr(0, 2) != "+7" || phone.find_first_not_of(phoneSym) != std::string::npos)
		return false;
	std::string name;
	ssReq >> name;
	std::string nameFirst;
	nameFirst = name[0];
	std::string nameOther;
	nameOther = name.substr(1);
	if (nameFirst.find_first_not_of(nameSymUp) != std::string::npos || nameOther.find_first_not_of(nameSymLow) != std::string::npos)
		return false;
	return true;
}

std::map<std::string, std::string> PhoneBook::byNumber;
std::multimap<std::string, std::string> PhoneBook::byName;

int main() {
	std::cout << "**COMMANDS: add, call, sms, exit**\n\n";
	Note* notes = new Note();
	std::string operation;
	std::string request;
	while (true) {
		std::cout << "Enter operation: ";
		std::cin >> operation;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (operation == "add") {
			std::cout << "Enter number(+7) and name: ";
			getline(std::cin, request);
			if (!requestParser(request)) {
				std::cerr << "\n**INVALID REQUEST**\n\n";
				continue;
			}
			std::string phone;
			std::string name;
			std::istringstream ssReq(request);
			ssReq >> phone >> name;

			auto phoneExist = PhoneBook::getByNumber().find(phone);
			if (phoneExist != PhoneBook::getByNumber().end()) {
				std::cerr << "\n**NUMBER ALREADY EXISTS**\n\n";
				continue;
			}
			notes->setNote(phone, name);
			PhoneBook::addNote(notes);
			std::cout << "\n<SUCCESSFUL ADDED>\n\n";

		}

		else if (operation == "call") {
			while (true) {
				std::cout << "Enter number(+7) or name: ";
				std::cin >> request;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				auto& phoneExist = PhoneBook::getByNumber().find(request);

				if (phoneExist != PhoneBook::getByNumber().end()) {
					std::cout << "\n>CALL " << request << std::endl << std::endl;
					break;
				}

				auto& nameExist = PhoneBook::getByName().equal_range(request);
				std::ptrdiff_t noteCount = std::distance(nameExist.first, nameExist.second);
				if (noteCount != 0) {
					if (noteCount == 1) {
						auto it = nameExist.first;
						std::cout << "\n>CALL " << it->second << std::endl << std::endl;
						break;
					}
					else if (noteCount > 1) {
						std::cout << "\n<SELECT>\n\n";
						for (auto it = nameExist.first; it != nameExist.second; ++it)
							std::cout << it->first << " " << it->second << std::endl;
						std::cout << std::endl;
						while (true) {
							std::cout << "Enter number: ";
							std::cin >> request;
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

							phoneExist = PhoneBook::getByNumber().find(request);
							if (phoneExist == PhoneBook::getByNumber().end()) {
								std::cerr << "\n**WRONG NUMBER**\n\n";
								continue;
							}

							std::cout << "\n>CALL " << request << std::endl << std::endl;
							break;
						}
					}
				}
				else {
					std::cerr << "\n**NOTE NOT EXISTS**\n\n";
					continue;
				}
				break;
			}
		}
	
		else if (operation == "sms") {
			while (true) {
				std::cout << "Enter number(+7) or name: ";
				std::cin >> request;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				auto& phoneExist = PhoneBook::getByNumber().find(request);
				std::string sms;
				if (phoneExist != PhoneBook::getByNumber().end()) {
					std::cout << "Enter sms: ";
					getline(std::cin, sms);
					std::cout << "\n>To " << request << "(" << phoneExist->second << "): " << sms << std::endl << std::endl;
					break;
				}

				auto& nameExist = PhoneBook::getByName().equal_range(request);
				std::ptrdiff_t noteCount = std::distance(nameExist.first, nameExist.second);
				if (noteCount != 0) {
					if (noteCount == 1) {
						auto it = nameExist.first;
						std::cout << "Enter sms: ";
						getline(std::cin, sms);
						std::cout << ">To " << request << "(" << it->second << "): " << sms << std::endl << std::endl;
						break;
					}
					else if (noteCount > 1) {
						std::cout << "\n<SELECT>\n\n";
						for (auto it = nameExist.first; it != nameExist.second; ++it)
							std::cout << it->first << " " << it->second << std::endl;
						std::cout << std::endl;
						while (true) {
							std::cout << "Enter number: ";
							std::cin >> request;
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

							phoneExist = PhoneBook::getByNumber().find(request);
							if (phoneExist == PhoneBook::getByNumber().end()) {
								std::cerr << "\n**WRONG NUMBER**\n\n";
								continue;
							}

							std::cout << "Enter sms: ";
							getline(std::cin, sms);
							std::cout << ">To " << request << "(" << phoneExist->second << "): " << sms << std::endl << std::endl;
							break;
						}
					}
				}
				else {
					std::cerr << "\n**NOTE NOT EXISTS**\n\n";
					continue;
				}
				break;
			}
		}

		else if (operation == "exit")
			break;
		else {
			std::cerr << "\n**UNKNOWN OPERATION**\n\n";
			continue;
		}
	}


}