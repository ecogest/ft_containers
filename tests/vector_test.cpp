#include "tests.hpp"

#include "vector.hpp"
#include <vector>

#include <string>

void	test_vector(void) {
/*
** ============================== CONSTRUCTORS ============================== **
*/

	// 1) Default constructor
	NS::vector<int>	v_int;

	// 2) With allocator
	std::allocator<char>	char_allocator;
	NS::vector<char>	v_char(char_allocator);
	// NS::vector<char>	v_char2((std::allocator<char>())); // why need 2 parentheses ?

	// 3) n elems with same value
	NS::vector<float>	v_10float(10);

	std::string	hello("hello");
	NS::vector<std::string>	v_3_hello(3, hello);

	// 5) TODO:

	// 6) copy constuctor
	NS::vector<std::string>	v_3_hello_copy(v_3_hello);
	const NS::vector<std::string>	v_3_hello_copy_const(v_3_hello);

/*
** ============================= Element access ============================= **
*/

	std::cout << v_10float.at(0) << v_3_hello.at(2) << std::endl;
	std::cout << v_10float[0] << v_3_hello[2] << std::endl;
	try {
		std::cout << v_3_hello.at(42) << std::endl;
	}
	catch (std::out_of_range const &ex) {
		std::cout << ex.what() << std::endl;
	}

	std::cout << v_3_hello_copy_const.at(1) << std::endl;
	std::cout << v_3_hello_copy_const[1] << std::endl;
	try {
		std::cout << v_3_hello_copy_const.at(3) << std::endl;
	}
	catch (std::out_of_range const &ex) {
		std::cout << ex.what() << std::endl;
	}
}
