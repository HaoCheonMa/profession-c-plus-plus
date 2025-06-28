#include "global_v.h"
#include "kbd.h"
#include "ram.h"
#include "cpu.h"
#include "gpu.h"
#include "disk.h"
#include <iostream>
#include <string>
#include <limits>
#include <sstream>

int main() {
	double data[buffer_size] = { 0 };
	std::cout << "\n**CMDs: sum, save, load, input, display, exit**\n\n";
	std::string cmd;
	std::string numbers;

	while (true) {
		std::cout << "Enter command: ";
		std::cin >> cmd;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (cmd == "input") {

			if (kbd_in(numbers)) {
				int i = 0;
				std::istringstream ss_numbers(numbers);
				while (ss_numbers >> data[i] && i < buffer_size)
					++i;
				write(data);
			}
			else {
				std::cerr << "\n**INVALID VALUES**\n\n";
				continue;
			}

		}
		else if (cmd == "save") {

			read(data);
			save(data);

		}
		else if (cmd == "load") {

			if (!load(data)) {
				std::cerr << "\n**FILE OPEN ERROR**\n\n";
				continue;
			}
			write(data);

		}
		else if (cmd == "display") {

			read(data);
			display(data);

		}
		else if (cmd == "sum") {

			read(data);
			std::cout << "\nBuffer sum: " << compute(data) << std::endl << std::endl;

		}
		else if (cmd == "exit")
			break;



		else
			std::cerr << "\n**UNKNOWN COMMAND**\n\n";

	}

	std::cout << "\n**PROGRAMM STOPPED**\n\n";

}