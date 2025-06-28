#include "cpu.h"
#include "global_v.h"

double compute(double* data) {
	double sum = 0;
	for (int i = 0; i < buffer_size; ++i)
		sum += data[i];
	return sum;
}