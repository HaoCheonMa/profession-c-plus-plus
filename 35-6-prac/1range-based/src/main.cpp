#include <iostream>
#include <vector>

template<typename T>
void printNums(std::initializer_list<T> valuesList)
{
	std::vector<T> valuesVec = valuesList;
	for (T num : valuesVec)
		std::cout << num << " ";
}

int main() 
{
	printNums({ 1, 2, 3, 4, 5 });
}