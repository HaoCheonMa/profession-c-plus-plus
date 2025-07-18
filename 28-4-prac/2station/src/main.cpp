#include "tools.h"
#include "train.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>
#include <vector>
#include <map>

using mapIt = std::map<time_t, char>::iterator;

std::condition_variable occuped;
std::mutex mtx;
bool stationFree = true;
bool allDone = false;
unsigned trainWas = 0;
std::queue<Train*> stationQueue;

std::string updateMark(int markNum) {
	std::string mark;
	switch (markNum) {
	case 1: mark = "A"; return mark;
	case 2: mark = "B"; return mark;
	case 3: mark = "C"; return mark;
	default: mark = "null"; return mark;
	}
}

void releaseTrain() {
	std::string released = "<Train " + stationQueue.front()->mark + " has departed from the station>" + "\n\n";
	mtx.lock();
	++trainWas;
	stationQueue.pop();
	stationFree = true;
	if (stationQueue.empty())
		std::cout << released;
	else {
		released.resize(released.size() - 1);
		std::cout << released;
		std::cout << "<Station is occuped by train " << stationQueue.front()->mark << ">\n\n";
	}
	occuped.notify_all();
	mtx.unlock();
}

void onStation(Train* train) {
	{
		std::unique_lock<std::mutex> lock(mtx);
		occuped.wait(lock, []() {return allDone; });
	}
	while (true) {
		--train->wayTime;
		if (train->wayTime == 0) {
			mtx.lock();
			stationFree = false;
			stationQueue.push(train);
			mtx.unlock();
		}
		else {
			sleep(1);
			continue;
		}
		break;
	}

	if (train->mark == stationQueue.front()->mark) {
		std::cout << "*\n\n";
		std::cout << "<Station is currently occupied by train " << train->mark << ">\n\n";
		std::cout << "Type \"depart\" to release the train: ";
	}
	else { 
		std::cout << "*\n\n";
		std::cout << "<Train " << train->mark << " is waiting in the queue>\n\n";
		std::cout << "Type \"depart\" to release the train: ";
	}

	{
		std::unique_lock<std::mutex> lock(mtx);
		occuped.wait(lock, []() {return stationFree; });
	}
}

int main(){
	std::vector<Train*> station;
	std::vector<std::thread*> trains;
	std::map<time_t, char> timeHistory;
	time_t lastTime = 0;
	for (size_t i = 0; i < Train::getCount(); ++i) {
		Train* train = nullptr;
		int trainMarkNum = i + 1;
		std::string trainMark = updateMark(trainMarkNum);
		std::string timeStr = input("Enter train " + trainMark + " way time(sec): ");
		time_t inWayTime = 0;
		if (isInt(timeStr)) {
			inWayTime = (time_t)std::stoi(timeStr);	
			mapIt timeFind = timeHistory.find(inWayTime);
			if (timeFind == timeHistory.end()) {
				timeHistory.insert({ inWayTime, '.' });
				train = new Train(trainMarkNum, trainMark, inWayTime);
			}
			else {
				std::cerr << "\n**SAME TIME**\n\n";
				--i;
				continue;
			}
		}
		else {
			std::cerr << "\n**INVALID INPUT**\n\n";
			--i;
			continue;
		}
		station.push_back(train);
	}

	for (size_t i = 0; i < Train::getCount(); ++i) {
		std::thread* trainIn = new std::thread(onStation, station[i]);
		trains.push_back(trainIn);
	}
		
	std::cout << std::endl;

	std::cout << std::setfill('0');
	for (size_t i = 0; i < Train::getCount(); ++i) {
		int hours = station[i]->wayTime / 3600;
		int minutes = (station[i]->wayTime % 3600) / 60;
		int seconds = station[i]->wayTime % 60;
		std::cout << "Train " << station[i]->mark << " will be on the way in ";
		std::cout << std::setw(2) << hours;
		std::cout << ":" << std::setw(2) << minutes;
		std::cout << ":" << std::setw(2) << seconds << std::endl;
	}
	std::cout << std::setfill(' ') << std::endl;

	mtx.lock();
	allDone = true;
	mtx.unlock();
	occuped.notify_all();

	while (trainWas != 3){
		std::string train = input("Type \"depart\" to release the train: ");
		std::cout << std::endl;
		if (train == "depart" && !stationQueue.empty())
			releaseTrain();
		else if (train == "depart" && stationQueue.empty())
			std::cerr << "**STATION IS FREE**\n\n";
		else std::cerr << "**ERROR**\n\n";
	}

	for (std::thread* train : trains)
		if (train->joinable()) train->join();

	for (Train* trainAway : station)
		delete trainAway;

	for (std::thread* trainAway : trains)
		delete trainAway;

	std::cout << "**ALL TRAINS HAVE ARRIVED AT THE STATION**\n";
}