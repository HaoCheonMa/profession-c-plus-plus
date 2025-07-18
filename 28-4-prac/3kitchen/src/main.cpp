#include "kitchen.h"
#include <iostream>
#include <thread>

int main() {

	std::thread waiter(ordering);
	waiter.detach();

	std::thread chef(cooking);
	chef.detach();

	std::thread service(deliveryService);
	service.detach();

	std::unique_lock<std::mutex> lock(end);
	final.wait(lock, []() {return Kitchen::getMax() == Kitchen::getDeliveries(); });

	std::cout << "\n**SUCCESFULL WORK**\n";
}