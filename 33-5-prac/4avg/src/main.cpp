#include <iostream>
#include <vector>
#include <sstream>
#include <limits>

template <typename T>
void input(std::vector<T>& vec, size_t size) {
    vec.resize(size);
    std::string line;
    while (true) {
        std::cout << "Fill the array (" << size << " elements) in one line: ";
        std::getline(std::cin, line);
        std::istringstream iss(line);

        bool valid = true;
        for (size_t i = 0; i < size; ++i) {
            if (!(iss >> vec[i])) {
                valid = false;
                break;
            }
        }

        T extra;
        if (iss >> extra) {
            valid = false;
        }

        if (!valid) {
            std::cout << "Invalid input or wrong number of elements. Please try again.\n";
        }
        else {
            break;
        }
    }
}

template <typename T>
double average(const std::vector<T>& vec) {
    double sum = 0;
    for (const auto& elem : vec) {
        sum += elem;
    }
    return sum / vec.size();
}

int main() {
    std::vector<double> vec;
    input(vec, 8);
    std::cout << "Average: " << average(vec) << std::endl;
    return 0;
}
