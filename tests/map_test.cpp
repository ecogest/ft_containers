#include <map>
#include <vector>
#include "tests.hpp"

void constructor_insert_and_iterator_test(void) {
	{ // empty constructor and regular inserts
		NS::map<std::string, int> M;
		std::cout << "-------------------" << std::endl;
		std::cout << "empty map:" << std::endl;
		for (NS::map<std::string, int>::iterator it = M.begin(); it != M.end(); it++)
			std::cout << *it << std::endl;
		std::cout << "-------------------" << std::endl;
		M.insert(NS::make_pair<std::string, int>("hello", 0));
		M.insert(NS::make_pair<std::string, int>("world", -42));
		M.insert(NS::make_pair<std::string, int>("map", 42));
		M.insert(NS::make_pair<std::string, int>("vector", 42));
		std::cout << "map(hello, world, map, vector):" << std::endl;
		for (NS::map<std::string, int>::iterator it = M.begin(); it != M.end(); it++)
			std::cout << *it << std::endl;
	}
	// create a vector of pairs for the following tests
	std::string	arr[] = { "hello", "world", "42", "!", "more", "words", "a", "b", "c", "d", "e" };
	NS::vector<std::string>	v(arr, arr + sizeof(arr) / sizeof(arr[0]));
	NS::vector<NS::pair<size_t, std::string> > v2;
	for (size_t i = 0; i < v.size(); i++)
		v2.push_back(NS::make_pair(i, v[i]));
	// insert with a vector iterator
	NS::map<size_t, std::string>	M(v2.begin(), v2.end());
	{ // print the map using regular iterator
		std::cout << "-------------------" << std::endl;
		std::cout << "MAP insert with vector iterator:" << std::endl;
		for (NS::map<size_t, std::string>::iterator it = M.begin(); it != M.end(); it++)
			std::cout << *it << std::endl;
	}
	{ // print with const_reverse_iterator
		std::cout << "-------------------" << std::endl;
		std::cout << "Print map with const_reverse_iterator:" << std::endl;
		for (NS::map<size_t, std::string>::const_reverse_iterator it = M.rbegin(); it != M.rend(); it++)
			std::cout << *it << std::endl;
	}
}

// See avl_test for more details concerning the structure
void	test_map(void) {
	std::cout << "===================" << std::endl;
	std::cout << "====== MAP ========" << std::endl;
	std::cout << "===================" << std::endl;
	constructor_insert_and_iterator_test();
}
