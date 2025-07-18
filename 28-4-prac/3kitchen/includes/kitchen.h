#pragma once

#include <string>
#include <mutex>
#include <condition_variable>

enum products {
	none, pizza, soup, steak, salad, sushi
};

class Kitchen {
	static constexpr unsigned maxDeliveries = 10;
	static size_t deliveries;
	static bool isFree;
	static size_t cooked;
public:
	unsigned curOrderNum = none;
	std::string product = "none";

	Kitchen(unsigned num) : curOrderNum(num){}

	static size_t getDeliveries() {
		return deliveries;
	}

	static void setSuccess() {
		++deliveries;
	}

	static size_t getCooked() {
		return cooked;
	}

	static void setCooked() {
		++cooked;
	}

	static void setStatus(bool free) {
		isFree = free;
	}

	static bool getStatus() {
		return isFree;
	}

	static constexpr unsigned getMax() {
		return maxDeliveries;
	}

	void updateOrder() {
		switch (curOrderNum) {
		case 1: product = "pizza"; break;
		case 2: product = "soup"; break;
		case 3: product = "steak"; break;
		case 4: product = "salad"; break;
		case 5: product = "sushi"; break;
		default: product = "none"; break;
		}
	}
};

extern std::mutex end;
extern std::condition_variable final;

void deliveryService();
void cooking();
void ordering();