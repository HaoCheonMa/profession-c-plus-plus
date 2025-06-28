#include "ram.h"
#include "global_v.h"
#include <string>
#include <sstream>

static double buffer[buffer_size] = { 0 };

void write(double* data) {

	for (int i = 0; i < buffer_size; ++i)
		buffer[i] = data[i];

}

void read(double* data) {

	for (int i = 0; i < buffer_size; ++i)
		data[i] = buffer[i];

}