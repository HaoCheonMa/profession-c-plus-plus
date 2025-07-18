#pragma once

#include <vector>
#include <string>

void sleep(size_t sec);

std::vector<std::string> strParsing(const std::string& request);

std::string input(const std::string& label);

int randInt(int minVal, int maxVal);

bool isWord(const std::string& word);

bool isNumber(const std::string& number);

bool isInt(const std::string& number);

bool isIntVector(const std::vector<std::string>& vec);