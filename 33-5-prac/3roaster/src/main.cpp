#include <iostream>
#include <memory>
#include <vector>
#include "tools.h"

template <typename K, typename V>
struct Data
{
	K key;
	V value;
	Data(K _key, V _value) : key(_key), value(_value){}
};

template <typename K, typename V>
class Registry
{
private:
	static std::vector <std::unique_ptr<Data<K, V>>> roster;
public:
	static void add(K key, V value)
	{
		roster.push_back(std::make_unique<Data<K, V>>(key, value));
	}
};

template <typename K, typename V>
std::vector <std::unique_ptr<Data<K, V>>> Registry<K, V>::roster;

int main()
{

}