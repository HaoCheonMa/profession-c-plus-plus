#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

class Branch {
public:
    Branch* parentBranch;
    std::vector<Branch*> childBranches;
    std::string elfName;

    Branch(Branch* parent = nullptr) : parentBranch(parent), elfName("") {}

    ~Branch() {
        for (Branch* child : childBranches) {
            delete child;
        }
    }

    Branch* findElf(const std::string& name) {
        if (elfName == name) return this;
        for (Branch* child : childBranches) {
            Branch* result = child->findElf(name);
            if (result) return result;
        }
        return nullptr;
    }

    Branch* getBigBranch() {
        if (parentBranch == nullptr) return nullptr;
        if (parentBranch->parentBranch == nullptr) return this;
        return parentBranch->getBigBranch();
    }

    int countElves() const {
        int count = elfName.empty() ? 0 : 1;
        for (const Branch* child : childBranches) {
            count += child->countElves();
        }
        return count;
    }
};

int randRange(int minVal, int maxVal) {
    return minVal + rand() % (maxVal - minVal + 1);
}

Branch* generateTree() {
    Branch* tree = new Branch(nullptr);
    int bigBranchCount = randRange(3, 5);

    for (int i = 0; i < bigBranchCount; ++i) {
        Branch* bigBranch = new Branch(tree);
        tree->childBranches.push_back(bigBranch);

        int midBranchCount = randRange(2, 3);
        for (int j = 0; j < midBranchCount; ++j) {
            Branch* midBranch = new Branch(bigBranch);
            bigBranch->childBranches.push_back(midBranch);
        }
    }
    return tree;
}

void collectHouses(Branch* branch, std::vector<Branch*>& houses) {
    if (branch->parentBranch != nullptr) {
        houses.push_back(branch);
    }
    for (Branch* child : branch->childBranches) {
        collectHouses(child, houses);
    }
}

int main() {
    srand(std::time(nullptr));

    const int treeCount = 5;
    std::vector<Branch*> forest;

    for (int i = 0; i < treeCount; ++i) {
        forest.push_back(generateTree());
    }

    std::vector<Branch*> allHouses;
    for (Branch* tree : forest) {
        collectHouses(tree, allHouses);
    }

    std::cout << "You will enter elf names for each house, one per line.\n";
    std::cout << "Enter 'None' if the house stays empty.\n";
    for (size_t i = 0; i < allHouses.size(); ++i) {
        std::cout << "House " << (i + 1) << " of " << allHouses.size() << ": ";
        std::string elfName;
        std::getline(std::cin, elfName);
        if (elfName != "None") {
            allHouses[i]->elfName = elfName;
        }
    }

    std::cout << "\nEnter the name of the elf to find neighbors of: ";
    std::string targetName;
    std::getline(std::cin, targetName);

    Branch* foundElf = nullptr;
    for (Branch* tree : forest) {
        foundElf = tree->findElf(targetName);
        if (foundElf != nullptr) break;
    }

    if (!foundElf) {
        std::cout << "Elf named \"" << targetName << "\" not found in the forest.\n";
    }
    else {
        Branch* bigBranch = foundElf->getBigBranch();
        if (bigBranch == nullptr) bigBranch = foundElf;

        int totalElves = bigBranch->countElves();
        int neighbors = totalElves - 1;

        std::cout << "Elf \"" << targetName << "\" lives with " << neighbors << " neighbors on their big branch.\n";
    }

    for (Branch* tree : forest) {
        delete tree;
    }
}
