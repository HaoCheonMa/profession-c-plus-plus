#include <iostream>
#include <vector>
#include <string>
#include "tools.h"

class Talent {
public:
	virtual std::string setTalent() = 0;
};

class Swimming : public Talent {
public:
	std::string setTalent() override { return "Swim"; }
};

class Dancing : public Talent {
public:
	std::string setTalent() override { return "Dance"; }
};

class Counting : public Talent {
public:
	std::string setTalent() override { return "Count"; }
};

class Dog{
	std::string name;
	std::vector<Talent*> talents;
public:
	Dog(std::string _name) : name(_name){}

    void addTalent(Talent* talent) {
        talents.push_back(talent);
    }

    void showTalents() {
        if (talents.empty()) {
            std::cout << "This is " << name << " and it has no talents.\n";
            return;
        }
        std::cout << "This is " << name << " and it has some talents:\n";
        for (Talent* talent : talents) {
            std::cout << "\tIt can \"" << talent->setTalent() << "\"\n";
        }
    }
};

int main() {
    Dog dog1("Steve");

    dog1.addTalent(new Dancing());
    dog1.addTalent(new Swimming());

    dog1.showTalents();
}