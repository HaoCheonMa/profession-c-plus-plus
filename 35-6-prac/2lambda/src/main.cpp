#include <iostream>
#include <vector>
#include <unordered_set>
#include <memory>

auto filterUnique = [](const std::vector<int>& numbers) -> std::unique_ptr<std::vector<int>> {
    std::unordered_set<int> seen;
    auto uniqueNumbers = std::make_unique<std::vector<int>>();

    for (auto num : numbers) {
        if (seen.find(num) == seen.end()) {
            seen.insert(num);          
            uniqueNumbers->push_back(num);
        }
    }

    return uniqueNumbers;
    };

int main() {
    std::vector<int> nums = { 1, 2, 2, 3, 4, 4, 5 };
    auto uniqueNumsPtr = filterUnique(nums);

    for (auto num : *uniqueNumsPtr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}