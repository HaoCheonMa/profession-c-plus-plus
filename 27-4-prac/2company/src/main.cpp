#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <vector>
#include <ctime>
//#include <map>
#include "tools.h"

enum taskTypes {N, A, B, C};

bool validData() {
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	return true;
}

class Employee {
	std::string name = "employer";
public:
	Employee(const std::string& name) : name(name) {}

	std::string getName() {
		return this->name;
	}
};

class Worker:public Employee {
public:
	int type = N;
	std::string taskType = "null";

	Worker(size_t index) : Employee("Worker" + std::to_string(index)) {}

	void updateType() {
		switch (type) {
		case 1: taskType = "A"; break;
		case 2: taskType = "B"; break;
		case 3: taskType = "C"; break;
		default: taskType = "null"; break;
		}
	}
};

class MiddleManager:public Employee {
public:
	std::vector<Worker> team;
	int totalWorkers = team.size();
	int freeWorkers = 0;
	int curTask = 0;
	int workersTasks = 0;
	bool teamBusy = false;
	MiddleManager(size_t index) : Employee("Manager" + std::to_string(index)) {}

	void giveTask(std::vector<bool>& busy) {
		freeWorkers = 0;
		std::string teamNumStr = this->getName();
		teamNumStr = teamNumStr[teamNumStr.length() - 1];
		int teamNum = std::stoi(teamNumStr);
		int hash = curTask + teamNum;
		std::srand(hash);
		for (int i = 0; i < team.size(); ++i)
			if (team[i].type == N)
				++freeWorkers;

		workersTasks = rand() % freeWorkers + 1;

		for (int i = 0; workersTasks != 0; ++i)
			if (team[i].type == N) {
				team[i].type = rand() % 3 + 1;
				team[i].updateType();
				--workersTasks;
				--freeWorkers;
			}

		//for (int i = 0; i < team.size(); ++i) {
		//	std::cout << "\t" << team[i].getName() << " have task: " << team[i].taskType << std::endl;
		//}

		if (freeWorkers == 0) {
			teamBusy = true;
			busy.push_back(true);
		}
	}
};

class CEO:public Employee {
public:
	std::vector<MiddleManager> personal;
	CEO() : Employee("CEO") {}

	bool setVectors(std::vector<int>& tasks) {
		int input = 1;
		std::string request;
		std::cout << "<SET VECTORS>\n\n";
		while (true) {
			std::cout << "CEO's vectors: ";
			getline(std::cin, request);
			std::vector<std::string> tasksStr = parsing(request);
			for (int i = 0; i < tasksStr.size(); ++i) {
				if (isInt(tasksStr[i]))
					input = std::stoi(tasksStr[i]);
				else return false;

				if (input > 0)
					tasks.push_back(input);
			}

			if (tasks.empty()){
				std::cerr << "\n**EMPTY VECTOR**\n\n";
				continue;
			}
			break;
		}
		return true;
	}

	void createCompany() {
		int input = 0;
		size_t size = 0;
		std::vector<size_t> teams;

		while (true) {
			std::cout << "Company teams: ";
			std::cin >> input;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (!validData() || input <= 0) {
				std::cerr << "\n**INVALID INPUT**\n\n";
				continue;
			}

			size = input;

			for (size_t i = 0; i < size; ++i) {
				std::cout << "Workers in team " << i + 1 << ": ";
				std::cin >> input;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				if (!validData() || input <= 0) {
					std::cerr << "\n**INVALID INPUT**\n\n";
					--i;
					continue;
				}
				teams.push_back(input);
			}

			break;

		}

		for (size_t i = 0; i < teams.size(); ++i) {
			MiddleManager manager(i + 1);
			for (size_t j = 0; j < teams[i]; ++j) {
				Worker worker(j + 1);
				manager.team.push_back(worker);
			}
			personal.push_back(manager);
		}
	}

	void getStatus() {
		std::cout << "\n<STATUS>\n";
		for (int i = 0; i < personal.size(); ++i) {
			std::cout << std::boolalpha << personal[i].getName() << " task: " << personal[i].curTask << std::endl;
			for (int j = 0; j < personal[i].team.size(); ++j)
				std::cout << "\t" << personal[i].team[j].getName() << " task: " << personal[i].team[j].taskType << std::endl;
			std::cout << std::endl;
		}
	}
};

//42
//17
//256
//99
//1234
//0

int main() {
	CEO* ceo = new CEO();
	std::vector<int> tasks;
	bool allBusy = false;

	ceo->createCompany();
	ceo->getStatus();

	std::vector<bool> busy;

	while (!allBusy) {
		tasks.clear();          
		if (!ceo->setVectors(tasks)) {
			std::cerr << "\n**INPUT ERROR**\n\n";
			continue;
		}

		int taskIndex = 0;
		int managerCount = ceo->personal.size();

		while (taskIndex < tasks.size()) {
			for (int i = 0; i < managerCount && taskIndex < tasks.size(); ++i) {
				if (!ceo->personal[i].teamBusy) {
					ceo->personal[i].curTask = tasks[taskIndex];
					/*std::cout << std::endl << ceo->personal[i].getName() << " have task: " << std::endl;*/
					ceo->personal[i].giveTask(busy);
					++taskIndex;
				}
			}
		}

		allBusy = (busy.size() == ceo->personal.size());

		if (!allBusy) {
			ceo->getStatus();
			std::cout << "**NO ALL TEAMS ARE BUSY**\n\n";
		}
		else
			break;
	}

	ceo->getStatus();
	std::cout << "<ALL BUSY>\n";

	delete ceo;
}