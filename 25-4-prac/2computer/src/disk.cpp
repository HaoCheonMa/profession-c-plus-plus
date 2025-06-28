#include "disk.h"
#include "global_v.h"
#include <fstream>
#include <iostream>

static const char* path = "../../../../data.txt";

void save(double* data) {

	std::ofstream data_save(path);
	for (int i = 0; i < buffer_size; ++i)
		data_save << data[i] << " ";
	data_save.close();
	std::cout << "\n>Saved" << std::endl << std::endl;

}

bool load(double* data) {

	std::ifstream data_save(path);
	if (data_save.is_open())
		for (int i = 0; i < buffer_size; ++i)
			data_save >> data[i];
	else
		return false;
	data_save.close();
	std::cout << "\n>Loaded" << std::endl << std::endl;
	return true;

}