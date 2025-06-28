#include "kbd.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <chrono>
#include <thread>
#include "global_v.h"

bool kbd_in(std::string& numbers) {
	std::cout << "Enter up to " << buffer_size << " numbers: ";
	getline(std::cin, numbers);
	double number = 0;
	int i = 0;
	std::istringstream ss_numbers(numbers);
	std::cout << std::endl;
	while (ss_numbers >> number && i < buffer_size) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << ">Success\n";
		++i;
	}
	if (!ss_numbers.eof() && i != 8) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << ">Fail\n\n";
		return false;
	}
	std::cout << std::endl;
	return true;

}