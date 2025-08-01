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

class Dog {
    std::string name;
    std::shared_ptr<Toy> toy;
public:
    Dog() = default;
    Dog(const std::string& _name, std::shared_ptr<Toy> _toy = nullptr) : name(_name), toy(_toy){}

    void getToy(std::shared_ptr<Toy> _toy) {
        if (toy == _toy)
            std::cerr << name << ": I already have " << toy->getName() << std::endl;
        else if (toy != nullptr)
            std::cerr << name << ": I already have toy\n";
        else if (_toy.use_count() > 2)
            std::cerr << name << ": Another dog is playing with " << _toy->getName() << std::endl;
        else {
            toy = _toy;
            std::cout << name << ": The " << toy->getName() << " taken\n";
        }

    }

    void dropToy() {
        if (toy == nullptr)
            std::cerr << name << ": Nothing to drop\n";
        else {
            std::cout << name << ": " << toy->getName() << " dropped\n";
            toy = nullptr;
        }
    }
};

int main() {
    std::shared_ptr<Toy> ball = std::make_shared<Toy>("Ball");
    std::shared_ptr<Toy> bone = std::make_shared<Toy>("Bone");


    Dog dog1("Buddy");
    Dog dog2("Max");

    dog1.getToy(ball);
    dog2.getToy(ball);
    dog2.getToy(bone);

    dog1.dropToy(); 
    dog2.getToy(ball);

    dog1.getToy(bone);

    dog2.dropToy();
    dog1.getToy(bone);

    dog1.dropToy();   
    dog1.dropToy();      
}
