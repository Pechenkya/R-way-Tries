#include <iostream>
#include <vector>
#include <string>
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

	A& operator=(A& obj)
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

	A(A& obj) : data{ obj.data }, name{ obj.name }, d{ obj.d }
	{
		std::cout << "A copyed" << std::endl;
	};

	A() : A(0, "Name") {};
};

int main()
{
	RwayTrie<A> new_tries;
	A dick(2, "dick chaney");
	new_tries.put("dog", dick);
	std::cout << new_tries.get_value("dog").data << " " << new_tries.get_value("dog").name << std::endl;
	new_tries.put("door", A(4, "short"));
	std::cout << new_tries.get_value("door").data << " " << new_tries.get_value("door").name << std::endl;

}
