#include <iostream>
#include <vector>
#include "RwayTrie.h"

class A
{
public:
	int data;
	double d;
	std::string name;

	A(int _data, std::string _name, double _d = 4.0) : data{ _data }, name{ _name }, d{ _d }
	{
		std::cout << "A created" << std::endl;
	};

	A& operator=(const A& obj)
	{
		this->data = obj.data;
		this->name = obj.name;
		this->d = obj.d;
		return *this;
	};

	A& operator=(A&& obj)
	{
		this->data = obj.data;
		this->name = obj.name;
		this->d = obj.d;
		return *this;
	};

	A(A&& obj) : data{ obj.data }, name{ obj.name }, d{ obj.d }
	{
		std::cout << "A moved" << std::endl;
	};

	A(const A& obj) : data{ obj.data }, name{ obj.name }, d{ obj.d }
	{
		std::cout << "A copyed" << std::endl;
	};

	A() : A(0, "Name") {};
};

int main()
{
	//RwayTrie<int, 8, std::vector<int>> new_trie;
	//std::vector<int> key1 = { 1, 5, 3, 5 };
	//new_trie.put(key1, 5);
	//new_trie.put(key1, 23);

	//std::vector <int> values = new_trie.get_value(key1);
	//for (auto t : values)
	//{
	//	std::cout << t << " ";
	//}

	RwayTrie<A, 256, std::string> new_tries;
	A dick(2, "dick chaney");
	new_tries.put("dog", dick);
	//std::vector<A> new_str = new_tries.get_value("dog");
	//std::cout << new_str[0].data << " " << new_str[0].name << std::endl;
	std::cout << new_tries.get_value("dog")[0].data << " " << new_tries.get_value("dog")[0].name << std::endl;
	new_tries.put("door", A(4, "short"));
}
