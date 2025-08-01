#include <iostream>
#include <string>
#include "tools.h"

class Toy {
public:
    Toy() = default;
    Toy(const std::string& _name) {
        name = _name;
    }
    std::string getName() {
        return name;
    }
    ~Toy() {
        std::cout << "Toy " << name << " was dropped " << std::endl;
    }
private:
    std::string name;
};

class shared_ptr_toy {
    Toy* toy = nullptr;
    size_t* links = nullptr;
public:

    shared_ptr_toy() = default;

    shared_ptr_toy(const std::string& _name) { 
        toy = new Toy(_name);
        links = new size_t(1);
    }

    shared_ptr_toy(const shared_ptr_toy& oth) {
        toy = oth.toy;
        links = oth.links;
        if (links)
            ++(*links);
    }

    void reset() {
        if (links) {
            --(*links);
            if (*links == 0) {
                delete toy;
                delete links;
            }
            toy = nullptr;
            links = nullptr;
        }
    }

    ~shared_ptr_toy() {
        reset();
    }

    shared_ptr_toy& operator=(const shared_ptr_toy& oth) {
        if (this != &oth) {
            reset();
            toy = oth.toy;
            links = oth.links;
            if (links)
                ++(*links);
        }

        return *this;
    }

    std::string getToyName() { 
        if (!toy)
            return "Nothing";
        return toy->getName(); 
    }
    size_t use_count() const { 
        if (!links)
            return 0;
        return *links; 
    }

    Toy* get() const { return toy; }
};

shared_ptr_toy make_shared_toy(const std::string& _name) { return shared_ptr_toy(_name); }

int main() {
    shared_ptr_toy toy_01 = make_shared_toy("ball");
    shared_ptr_toy toy_02(toy_01);
    shared_ptr_toy toy_03("duck");
    std::cout << "=================================================" << std::endl;
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
        << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;
    toy_02 = toy_03;
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
        << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;
    toy_01.reset();
    std::cout << toy_01.getToyName() << " links:" << toy_01.use_count() << "  "
        << toy_02.getToyName() << " links:" << toy_02.use_count() << "  "
        << toy_03.getToyName() << " links:" << toy_03.use_count() << std::endl;
    std::cout << "=================================================" << std::endl;

}
