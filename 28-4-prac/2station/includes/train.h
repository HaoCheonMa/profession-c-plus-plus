#pragma once
#include <ctime>
#include <string>

class Train {
	static constexpr int trainsCount = 3;
public:
	int markNum = 0;
	std::string mark = "null";
	time_t wayTime = 0;
	bool onStation = false;

	Train() = default;

	Train(int num, const std::string& letter, time_t sec) : markNum(num), mark(letter), wayTime(sec) {}

	static constexpr int getCount() {
		return trainsCount;
	}
};