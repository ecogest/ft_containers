#include <map>
#include <vector>
#include "tests.hpp"

void constructor_insert_and_iterator_test(void) {
	{ // empty constructor and regular inserts
		NS::map<std::string, int> M;
		std::cout << "-------------------" << std::endl;
		std::cout << "empty map:" << std::endl;
		for (NS::map<std::string, int>::iterator it = M.begin(); it != M.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << "-------------------" << std::endl;
		M.insert(NS::make_pair<std::string, int>("hello", 0));
		M.insert(NS::make_pair<std::string, int>("world", -42));
		M.insert(NS::make_pair<std::string, int>("map", 42));
		M.insert(NS::make_pair<std::string, int>("vector", 42));
		std::cout << "map(hello, world, map, vector):" << std::endl;
		for (NS::map<std::string, int>::iterator it = M.begin(); it != M.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
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
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	{ // print with const_reverse_iterator
		std::cout << "-------------------" << std::endl;
		std::cout << "Print map with const_reverse_iterator:" << std::endl;
		for (NS::map<size_t, std::string>::const_reverse_iterator it = M.rbegin(); it != M.rend(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	{ // copy constructor and operator =
		std::cout << "-------------------" << std::endl;
		std::cout << "Copy constructor" << std::endl;
		NS::map<size_t, std::string>	N(M);
		for (NS::map<size_t, std::string>::const_reverse_iterator it = N.rbegin(); it != N.rend(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << "-------------------" << std::endl;
		std::cout << "Copy constructor and assignation: check this is deep copy" << std::endl;
		NS::map<size_t, std::string>	O(N); // COPY CONSTRUCTOR
		NS::map<size_t, std::string>	P;
		P.insert(NS::make_pair<size_t, std::string>(42, "hi42!"));
		P = N; // ASSIGNATION
		N.erase(N.begin());
		N.erase(N.begin());
		N.erase(N.begin());
		N.erase(++N.begin());
		for (NS::map<size_t, std::string>::const_reverse_iterator it = N.rbegin(); it != N.rend(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		for (NS::map<size_t, std::string>::const_reverse_iterator it = O.rbegin(); it != O.rend(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		for (NS::map<size_t, std::string>::const_reverse_iterator it = P.rbegin(); it != P.rend(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;

	}
	{ // find
		std::cout << *M.find(0) << std::endl;
		std::cout << *M.find(1) << std::endl;
		std::cout << *M.find(2) << std::endl;
		std::cout << *M.find(7) << std::endl;
		(*M.find(7)).second = "AAA";
		std::cout << *M.find(7) << std::endl;
		if (M.find(42) != M.end())
			std::cout << *M.find(42) << std::endl;
		else
			std::cout << "NOT FOUND" << std::endl;
		// try {
		// 	std::cout << *M.find(42) << std::endl;
		// }
		// catch (std::out_of_range const &except) {
		// 	std::cout << except.what() << std::endl;
		// }
	}
	{ // const find
		NS::map<size_t, std::string> const N(M);
		std::cout << *N.find(0) << std::endl;
		std::cout << *N.find(1) << std::endl;
		std::cout << *N.find(2) << std::endl;
		std::cout << *N.find(7) << std::endl;
		if (N.find(42) != N.end())
			std::cout << *N.find(42) << std::endl;
		else
			std::cout << "NOT FOUND" << std::endl;
	}
	{ // at
		std::cout << M.at(0) << std::endl;
		std::cout << M.at(1) << std::endl;
		std::cout << M.at(2) << std::endl;
		std::cout << M.at(7) << std::endl;
		M.at(7) = "WWW";
		std::cout << M.at(7) << std::endl;
		try {
			std::cout << M.at(42) << std::endl;
		}
		catch (std::out_of_range const &except) {
			std::cout << except.what() << std::endl;
		}
	}
	{ // const at
		NS::map<size_t, std::string> const N(M);
		std::cout << N.at(0) << std::endl;
		std::cout << N.at(1) << std::endl;
		std::cout << N.at(2) << std::endl;
		std::cout << N.at(7) << std::endl;
		try {
			std::cout << N.at(42) << std::endl;
		}
		catch (std::out_of_range const &except) {
			std::cout << except.what() << std::endl;
		}
	}
}

// See avl_test for more details concerning the structure
void	test_map(void) {
	std::cout << "===================" << std::endl;
	std::cout << "====== MAP ========" << std::endl;
	std::cout << "===================" << std::endl;
	constructor_insert_and_iterator_test();
}
