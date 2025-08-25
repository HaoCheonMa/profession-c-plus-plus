#include <iostream>
#include <cstdint>
#include <utility>
#include <exception>
#include <string>
#include <map>
#include <set>
#include "tools.h"

class Success : public std::exception 
{
	const char* msg;
public:
	Success(const char* _msg) : msg(_msg){}
	const char* what() const noexcept override
	{
		return msg;
	}
};

class Fail : public std::exception
{
	const char* msg;
public:
	Fail(const char* _msg) : msg(_msg) {}
	const char* what() const noexcept override
	{
		return msg;
	}
};

class Again : public std::exception
{
	const char* msg;
public:
	Again(const char* _msg) : msg(_msg) {}
	const char* what() const noexcept override
	{
		return msg;
	}
};

class Fishing 
{
	static constexpr uint8_t pondSize = 9;
	static char pond[pondSize];
	static constexpr uint8_t objectsAmount = 4;
	static std::map<int8_t, const char*> objects;

public:

	static const uint8_t getSize()
	{
		return pondSize;
	}

	static void createPond()
	{
		try
		{
			const char* msg = "No objects here\nGenerating empty field";
			if (objects.empty())
				throw std::runtime_error(msg);

			for (uint8_t i = 0; i < pondSize; ++i)
			{
				auto itObjects = objects.find(i);
				if (itObjects != objects.end())
				{
					if (itObjects->second == "fish")
						pond[i] = 'F';
					else if (itObjects->second == "boot")
						pond[i] = 'B';
					else
						pond[i] = '.';
				}
			}
			std::cout << std::endl;
			return;
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
		}

		for (uint8_t i = 0; i < pondSize; ++i)
			pond[i] = '.';
		std::cout << std::endl;
	}

	static void printPond()
	{
		uint8_t count = 0;
		for (uint8_t i = 0; i < pondSize; ++i)
		{
			std::cout << pond[i] << " ";
			++count;
			if (count == 3 && i != 8)
			{
				std::cout << std::endl;
				count = 0;
			}
		}
		std::cout << std::endl;
	}

	static void generateObjects() 
	{
		std::set<uint8_t> occupiedSectors;
		uint8_t sector = randInt(0, pondSize - 1);
		occupiedSectors.insert(sector);
		objects.insert({ sector, "fish" });

		while (occupiedSectors.size() != objectsAmount)
		{
			try
			{
				sector = randInt(0, pondSize - 1);
				if (occupiedSectors.find(sector) != occupiedSectors.end())
					throw std::invalid_argument("Sector already used");

				occupiedSectors.insert(sector);
				objects.insert({ sector, "boot" });

			}
			catch (const std::invalid_argument& e)
			{
			}
		}
		Fishing::createPond();
	}

	static bool castingRod(int8_t sector)
	{
		sleep(1);
		std::cout << "Casting a fishing rod...\n\n";
		sleep(1);

		try
		{
			if (pond[sector] == 'F')
				throw Success("You actually catch a fish");
			else if (pond[sector] == 'B')
				throw Fail("You actually catch a boot");
			else
				throw Again("The fish was not here");
					
		}
		catch (const Success& e)
		{
			std::cout << "Success! " << e.what() << std::endl << std::endl;
			sleep(1);
			return true;
		}
		catch (const Fail& e)
		{
			std::cerr << "Fail! " << e.what() << std::endl << std::endl;
			sleep(1);
			return true;
		}
		catch (const Again& e)
		{
			std::cerr << "Try again. " << e.what() << std::endl << std::endl;
			sleep(1);
			return false;
		}	
	}
};

static int safeStoi(const std::string& s) {
	try {
		return std::stoi(s);
	}
	catch (const std::invalid_argument&) {
		throw std::invalid_argument("number converting error");
	}
	catch (const std::out_of_range&) {
		throw std::invalid_argument("number converting error");
	}
}

char Fishing::pond[pondSize];
std::map<int8_t, const char*> Fishing::objects;

int main() 
{
	Fishing::createPond();
	Fishing::printPond();
	Fishing::generateObjects();

	uint8_t tries = 0;
	bool gameEnd = false;
	while (tries != Fishing::getSize() && !gameEnd)
	{
		std::cout << "Enter sector num: ";
		std::string sectorStr = input();
		std::cout << std::endl;

		try
		{
			int8_t sectorNum = safeStoi(sectorStr) - 1;
			if (sectorNum < 0)
				throw std::invalid_argument("No playable sector");
			gameEnd = Fishing::castingRod(sectorNum);
			++tries;
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << "Error: " << e.what() << std::endl << std::endl;
		}
	}

	Fishing::printPond();
	std::cout << std::endl;
	std::cout << "Tries: " << (int)tries << std::endl;
}