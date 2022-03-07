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
}
