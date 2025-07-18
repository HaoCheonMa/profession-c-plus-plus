#include "kitchen.h"
#include "tools.h"
#include <iostream>
#include <cstdlib>
#include <queue>

std::mutex end;
std::condition_variable final;

size_t Kitchen::deliveries = 0;
bool Kitchen::isFree = true;
size_t Kitchen::cooked = 0;

std::condition_variable ordered;
std::condition_variable deliver;
std::queue<Kitchen*> orders;
std::queue<Kitchen*> delivers;
std::mutex mtx;


void deliveryService() {
	while (Kitchen::getDeliveries() != Kitchen::getMax()) {
		{
			std::unique_lock<std::mutex> lock(mtx);
			deliver.wait(lock, []() {return !delivers.empty(); });
			std::cout << "<The courier delivers the " << delivers.front()->product << ">" << std::endl;
		}
		{
			sleep(30);
			std::unique_lock<std::mutex> lock(mtx);
			std::cout << "<The " << delivers.front()->product << " has been delivered>" << std::endl;
			Kitchen* finished = delivers.front();
			delivers.pop();
			delete finished;
			Kitchen::setSuccess();
			deliver.notify_one();
		}
	}

	final.notify_one();
}

void cooking() {
	while (Kitchen::getCooked() != Kitchen::getMax()) {
		{
			std::unique_lock<std::mutex> lock(mtx);
			ordered.wait(lock, []() { return !orders.empty(); });
			std::cout << "<Cooking " << orders.front()->product << ">" << std::endl;
		}
		sleep(randInt(5, 15));
		{
			std::unique_lock<std::mutex> lock(mtx);
			std::cout << "<" << orders.front()->product << " is cooked>" << std::endl;
			Kitchen::setCooked();
			delivers.push(orders.front());
			orders.pop();
			deliver.notify_one();
		}
	}
}

void ordering() {
	for (size_t i = 0; i < Kitchen::getMax(); ++i) {
		Kitchen* order = nullptr;
		unsigned product = randInt(1, 5);
		order = new Kitchen(product);
		order->updateOrder();
		{
			std::unique_lock<std::mutex> lock(mtx);
			orders.push(order);
			std::cout << "Order " << i + 1 << ". " << order->product << std::endl;
			ordered.notify_one();
		}
		sleep(randInt(5, 10));
	}
}