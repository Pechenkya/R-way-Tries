#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>

template <typename T, size_t R = 256, typename Container = std::vector<char>>
class RwayTrie
{
	struct Node;

	std::shared_ptr<Node> root = std::shared_ptr<Node>(new Node());

	int get_node(int index, Container key);

	template<typename N>
	void put(Node* &node, Container key, N&& value, int d = 0);

	std::vector<T> get_value(Node* node, Container key, int d = 0);
	bool remove_value(Node* &node, Container key, int d = 0);

public:
	void put(Container key, T&& value);
	void put(Container key, T& value);
	std::vector<T> get_value(Container key);
	void remove_value(Container key);
};


template <typename T, size_t R, typename Container>
struct RwayTrie<T, R, Container>::Node
{
	std::vector<bool> deletable = { false };
	std::vector<T*> value = { nullptr };
	Node* next[R] = { nullptr }; //Array of pointers to next nodes
	
	bool no_next();

	~Node();
};


template <typename T, size_t R, typename Container>
bool RwayTrie<T, R, Container>::Node::no_next()
{
	for (auto t : this->next)
	{
		if (t != nullptr)
			return false;
	}
	return true;
}

template <typename T, size_t R, typename Container>
RwayTrie<T, R, Container>::Node::~Node()
{
	for (unsigned int i = 0; i < this->value.size(); i++)
		if (this->deletable[i])
			delete value[i];

	for (Node* &p : next)
		delete p;
}


template <typename T, size_t R, typename Container>
int RwayTrie<T, R, Container>::get_node(int index, Container key)
{
	return static_cast<int>(key[index]);
}

template <typename T, size_t R, typename Container>
template<typename N>
void RwayTrie<T, R, Container>::put(Node* &node, Container key, N&& value, int d)
{
	if (!node) node = new Node;
	if (d == key.size())
	{
		if constexpr (std::is_lvalue_reference<N>::value)
		{
			node->value.push_back(&value);
			node->deletable.push_back(false);
		}
		else
		{
			node->value.push_back(new T(std::forward<N>(value)));
			node->deletable.push_back(true);
		}
		std::cout << "Adding succesful!" << std::endl;
		return;
	}
	int c = get_node(d, key);
	put(node->next[c], key, std::forward<N>(value), d + 1);
}

template <typename T, size_t R, typename Container>
std::vector<T> RwayTrie<T, R, Container>::get_value(Node* node, Container key, int d)
{
	if (d == key.size())
	{
		if (!(node && node->value.size() != 1))
		{
			std::cout << "Key doesn't exist!" << std::endl;
			return {};
		}
		else
		{
			std::vector<T> temp_v;
			for (unsigned int i = 1; i < node->value.size(); i++)
				temp_v.push_back(*node->value[i]);
			return temp_v;
		}
	}

	if (!node)
	{
		std::cout << "Key doesn't exist!" << std::endl;
		return {};
	}

	int c = get_node(d, key);
	return get_value(node->next[c], key, d + 1);
}

template <typename T, size_t R, typename Container>
bool RwayTrie<T, R, Container>::remove_value(Node* &node, Container key, int d)
{
	if (d == key.size())
	{
		if (!(node && node->value.size() != 1))
		{
			return true;
		}
		else
		{
			if (node->no_next())
			{
				node->~Node();
				node = nullptr;
				return false;
			}
			else
			{
				for (unsigned int i = node->value.size() - 1; i >= 1 ; i--)
					if (node->deletable[i])
					{
						delete node->value[i];
						node->value.pop_back();
						node->deletable.pop_back();
					}

				return true;
			}
		}
	}

	if (!node)
	{
		std::cout << "Key doesn't exist!" << std::endl;
		return true;
	}

	int c = get_node(d, key);
	bool removing_complete = remove_value(node->next[c], key, d + 1);

	if (removing_complete)
		return true;

	if (node->value.size() == 1 && node->no_next())
	{
		node->~Node();
		node = nullptr;
		return false;
	}
	else
		return true;

}

template <typename T, size_t R, typename Container>
void RwayTrie<T, R, Container>::put(Container key, T&& value)	//User call function (rvalue)
{
	Node* temp_ptr = this->root.get();
	put(temp_ptr, key, std::forward<T>(value));
}

template <typename T, size_t R, typename Container>
void RwayTrie<T, R, Container>::put(Container key, T& value)	//User call function (lvalue)
{
	Node* temp_ptr = this->root.get();
	put(temp_ptr, key, std::forward<T>(value));
}

template <typename T, size_t R, typename Container>
std::vector<T> RwayTrie<T, R, Container>::get_value(Container key)
{
	Node* temp_ptr = this->root.get();
	return get_value(temp_ptr, key);
}

template <typename T, size_t R, typename Container>
void RwayTrie<T, R, Container>::remove_value(Container key)
{
	Node* temp_ptr = this->root.get();
	remove_value(temp_ptr, key);
}