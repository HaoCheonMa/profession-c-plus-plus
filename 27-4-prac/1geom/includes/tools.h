#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> parsing(std::string& request) {
	std::vector<std::string> strParts;
	std::string temp;
	std::istringstream ssRequest(request);
	while (ssRequest >> temp)
		strParts.push_back(temp);
	return strParts;
}

bool isWord(const std::string& word) {
	std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	if (word.find_first_not_of(letters) != std::string::npos)
		return false;
	return true;
}

bool isNumber(const std::string& number) {
	if (number == "-" || number == "." || number == "-.")
		return false;
	
	std::string digits = "-.1234567890";

	short negative = 0;
	short separate = 0;
	if (number.find_first_not_of(digits) != std::string::npos)
		return false;
	for (int i = 0; i < number.length(); ++i) {
		if (number[i] == '-')
			++negative;
		if (number[i] == '.')
			++separate;
		if (separate > 1 || negative > 1)
			return false;
	}

	if (negative == 1 && number[0] != '-')
		return false;

	return true;
}

bool isInt(const std::string& number) {
	if (number == "-" || number == "." || number == "-.")
		return false;

	std::string digits = "-1234567890";

	short negative = 0;
	if (number.find_first_not_of(digits) != std::string::npos)
		return false;

	for (int i = 0; i < number.length(); ++i) {
		if (number[i] == '-')
			++negative;
		if (negative > 1)
			return false;
	}

	if (negative == 1 && number[0] != '-')
		return false;

	return true;
}

bool isIntVector(std::vector<std::string>& vec) {
	for (int i = 0; i < vec.size(); ++i) 
		if (!isInt(vec[i]))
			return false;
	return true;
}