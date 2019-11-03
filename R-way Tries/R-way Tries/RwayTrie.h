#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>

int get_char(char c)
{
	return static_cast<int>(c);
}

template <typename T, size_t R = 256>
class RwayTrie
{
	struct Node;

	std::shared_ptr<Node> root = std::shared_ptr<Node>(new Node());

	template<typename N>
	void put(Node* &node, std::string key, N&& value, int d = 0);

	T get_value(Node* node, std::string key, int d = 0);

public:
	void put(std::string key, T&& value);
	void put(std::string key, T& value);
	T get_value(std::string key);
};


template <typename T, size_t R>
struct RwayTrie<T, R>::Node
{
	bool deletable = false;
	T* value = nullptr;
	Node* next[R] = {nullptr}; //Array of pointers to next nodes

	~Node();
};



template<typename T, size_t R>
RwayTrie<T, R>::Node::~Node()
{
	if (this->deletable)
		delete value;

	for (Node* &p : next)
		delete p;
}


template<typename T, size_t R>
template<typename N>
void RwayTrie<T, R>::put(Node* &node, std::string key, N&& value, int d)
{
	if (!node) node = new Node;
	if (d == key.length())
	{
		if constexpr (std::is_lvalue_reference<N>::value)
		{
			node->value = &value;
		}
		else
		{
			node->value = new T(std::forward<N>(value));
			node->deletable = true;
		}
		std::cout << "Adding succesful!" << std::endl;
		return;
	}
	int c = get_char(key[d]);
	put(node->next[c], key, std::forward<N>(value), d + 1);
}

template<typename T, size_t R>
T RwayTrie<T, R>::get_value(Node* node, std::string key, int d)
{
	if (d == key.length())
	{
		if ( !(node && node->value) )
		{
			std::cout << "Key doesn't exist!" << std::endl;
			return T();
		}
		else
		{
			return *node->value;
		}
	}

	if (!node)
	{
		std::cout << "Key doesn't exist!" << std::endl;
		return T();
	}
	
	int c = get_char(key[d]);
	return get_value(node->next[c], key, d + 1);
}

template<typename T, size_t R>
void RwayTrie<T, R>::put(std::string key, T&& value)	//User call function (rvalue)
{
	Node* temp_ptr = this->root.get();
	put(temp_ptr, key, std::forward<T>(value));
}

template<typename T, size_t R>
void RwayTrie<T, R>::put(std::string key, T& value)	//User call function (lvalue)
{
	Node* temp_ptr = this->root.get();
	put(temp_ptr, key, std::forward<T>(value));
}

template<typename T, size_t R>
T RwayTrie<T, R>::get_value(std::string key)
{
	Node* temp_ptr = this->root.get();
	return get_value(temp_ptr, key);
}
