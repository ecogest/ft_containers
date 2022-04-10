#include <map>
#include "tests.hpp"


// See avl_test for more details concerning the structure
void	test_map(void) {
	ft::map<std::string, int> M;
	M.insert(ft::make_pair<std::string, int>("hello", 0));
	M.insert(ft::make_pair<std::string, int>("world", -42));
	M.insert(ft::make_pair<std::string, int>("map", 42));
	M.insert(ft::make_pair<std::string, int>("vector", 42));
	M.print();
	std::map<std::string, std::string> N;

}
