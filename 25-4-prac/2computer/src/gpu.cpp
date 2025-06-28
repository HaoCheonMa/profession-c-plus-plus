#include "gpu.h"
#include "global_v.h"
#include <iostream>

void display(double* data) {
	std::cout << "\nRam buffer: ";
	for (int i = 0; i < buffer_size; ++i)
		std::cout << data[i] << " ";
	std::cout << std::endl << std::endl;
}