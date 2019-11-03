//#include "RwayTries.h"
//#include <iostream>
//
//
//int get_char(char c) 
//{
//	return static_cast<int>(c);
//}
//
//
//
//template<typename T>
//const size_t RwayTries<T>::R;  //Count of characters in extended ASCII
//
//template<typename T>
//void RwayTries<T>::put(Node<T>* node, std::string key, T value, int d)
//{
//	if (node == nullptr) node = new Node<T>();
//	if (d == key.length())
//	{
//		node->value = value;
//		std::cout << "Adding successful!" << std::endl;
//		return;
//	}
//	int c = get_char(key[d]);
//	put(&node->next[c], key, value, d + 1);
//}
//
//template<typename T>
//T RwayTries<T>::get_value(Node<T>* node, std::string key, int d)
//{
//	if(node == nullptr) throw ("Key '" + key + "' doesn't exist!");
//	int c = get_char(key[d]);
//	return get_value(&node->next[d], key, d + 1);
//}
//
//template<typename T>
//void RwayTries<T>::put(std::string key, T value)	//User call function
//{
//	put(this->root, key, value);
//}
//
//template<typename T>
//T RwayTries<T>::get_value(std::string key)
//{
//	return get_value(this->root, key);
//}
