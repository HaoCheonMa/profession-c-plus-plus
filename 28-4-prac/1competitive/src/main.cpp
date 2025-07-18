#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include "tools.h"

std::mutex action;
std::condition_variable race;
const int trackLength = 100;
const int swimmersCount = 6;
bool allDone = false;

class Competition {
public:
	std::string swimmerName;
	int trackNum;
	int finishSeconds = 0;

	Competition(std::string name, size_t number) : swimmerName(name), trackNum(number) {}
};

void swim(Competition* swimmer) {
	{
		std::unique_lock<std::mutex> lock(action);
		race.wait(lock, []() { return allDone; });
	}
	int distance = 0;
	while (distance < trackLength) {
		++swimmer->finishSeconds;
		distance += randInt(1, randInt(3, trackLength));
		if (distance > trackLength)
			distance = trackLength;
		{
			std::lock_guard<std::mutex> guard(action);
			std::cout << swimmer->swimmerName << " distance: " << distance << std::endl;
		}
		SLEEP(1);
	}
}

int main() {
	std::srand(std::time(nullptr));
	std::vector<Competition*> competitors(swimmersCount, nullptr);
	std::vector<std::thread*> prepare;
	bool competitionEnd = false;
	
	for (size_t i = 0; i < swimmersCount; ++i) {
		std::string name = input(std::to_string(i+1) + ". Swimmer's name: ");
		Competition* swimmer = new Competition(name, i);
		competitors[i] = swimmer;
		std::thread* onStart = new std::thread(swim, competitors[i]);
		prepare.push_back(onStart);
		if (prepare.size() == competitors.size()) {
			std::cout << "\n<START COMPETITIVE>\n\n";
			{
				std::lock_guard<std::mutex> lock(action);
				allDone = true;
			}
			race.notify_all();
		}
	}

	for (size_t i = 0; i < prepare.size(); ++i)
		if (prepare[i]->joinable()) prepare[i] -> join();

	for (size_t i = 0; i < competitors.size() - 1; ++i) {
		size_t minIndex = i;
		for (size_t j = i + 1; j < competitors.size(); ++j)
			if (competitors[j]->finishSeconds < competitors[minIndex]->finishSeconds)
				minIndex = j;

		if (minIndex != i)
			std::swap(competitors[i], competitors[minIndex]);
	}

	std::cout << "\n<MEMBERS>\n\n";
	for (size_t i = 0; i < competitors.size(); ++i)
		std::cout << i+1 << ". " << competitors[i]->swimmerName << " finished in: " << competitors[i]->finishSeconds << std::endl;
	std::cout << std::endl;

	for (std::thread* swimmer : prepare)
		delete swimmer;

	for (Competition* swimmer : competitors)
		delete swimmer;
}