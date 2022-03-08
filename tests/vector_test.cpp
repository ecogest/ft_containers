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
	std::cout << v_10float[0] << v_3_hello[2] << std::endl;
	std::cout << v_3_hello.front() << std::endl;
	try {
		std::cout << v_3_hello.at(42) << std::endl;
	}
	catch (std::out_of_range const &ex) {
		std::cout << ex.what() << std::endl;
	}

	std::cout << v_3_hello_copy_const.at(2) << std::endl;
	std::cout << v_3_hello_copy_const[2] << std::endl;
	std::cout << v_3_hello_copy_const.front() << std::endl;
	try {
		std::cout << v_3_hello_copy_const.at(42) << std::endl;
	}
	catch (std::out_of_range const &ex) {
		std::cout << ex.what() << std::endl;
	}

/*
** ================================ Capacity ================================ **
*/
	std::cout << "cap:" << v_int.capacity() << ",size:" << v_int.size() << ",max_size:" << v_int.max_size() << ",empty:" << v_int.empty() << std::endl;
	std::cout << "cap:" << v_10float.capacity() << ",size:" << v_10float.size() << ",max_size:" << v_10float.max_size() << ",empty:" << v_10float.empty() << std::endl;
	std::cout << "cap:" << v_3_hello_copy_const.capacity() << ",size:" << v_3_hello_copy_const.size() << ",max_size:" << v_3_hello_copy_const.max_size() << ",empty:" << v_3_hello_copy_const.empty() << std::endl;
	v_3_hello_copy.reserve(142);
	std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
	v_3_hello_copy.reserve(1);
	std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
	v_3_hello_copy.reserve(9);
	std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
	try {
		v_3_hello_copy.reserve(v_3_hello_copy.max_size() - 1);
	} catch (std::exception const &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		v_3_hello_copy.reserve(v_3_hello_copy.max_size());
	} catch (std::exception const &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		v_3_hello_copy.reserve(v_3_hello_copy.max_size() + 1);
	} catch (std::exception const &e) {
		std::cout << e.what() << std::endl;
	}
	v_3_hello.reserve(3);
}
