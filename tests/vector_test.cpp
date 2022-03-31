#include "tests.hpp"

#include "vector.hpp"
#include <vector>

#include <string>

#include <iterator>
// #include <map>
#include <deque>

template <typename vec>
void	print_vector(vec v) {
	for (typename vec::iterator it = v.begin(); it !=v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

/*
** ============================== CONSTRUCTORS ============================== **
*/

static void constructors() {
	// 1) Default constructor
	NS::vector<int>	v_int;

	// 2) With allocator
	std::allocator<char>	char_allocator;
	NS::vector<char>	v_char(char_allocator);
	// NS::vector<char>	v_char2((std::allocator<char>())); // why need 2 parentheses ?

	// 3) n elems with same value
	NS::vector<float>	v_10float(10);
	print_vector(v_10float);

	std::string	hello("hello");
	NS::vector<std::string>	v_3_hello(3, hello);
	print_vector(v_3_hello);

	// 5) using iterators
	NS::vector<std::string> copy_with_iterator(v_3_hello.begin(), v_3_hello.end());
	print_vector(copy_with_iterator);

	// 6) copy constuctor
	NS::vector<std::string>	v_3_hello_copy(v_3_hello);
	print_vector(v_3_hello_copy);
	const NS::vector<std::string>	v_3_hello_copy_const(v_3_hello);
	print_vector(v_3_hello_copy_const);
}


/*
** ============================= Element access ============================= **
*/

static void element_access() {
	NS::vector<float>	v_10float(10);
	std::string			hello("hello");
	NS::vector<std::string>	v_3_hello(3, hello);

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

	NS::vector<std::string>	v_3_hello_copy(v_3_hello);
	const NS::vector<std::string>	v_3_hello_copy_const(v_3_hello);
	std::cout << v_3_hello_copy_const.at(2) << std::endl;
	std::cout << v_3_hello_copy_const[2] << std::endl;
	std::cout << v_3_hello_copy_const.front() << std::endl;
	try {
		std::cout << v_3_hello_copy_const.at(42) << std::endl;
	}
	catch (std::out_of_range const &ex) {
		std::cout << ex.what() << std::endl;
	}

	NS::vector<int>	v_int;
	std::cout << (v_int.data() == NULL) << std::endl;
	std::cout << (v_3_hello.data() != NULL) << std::endl;
	v_3_hello[2] = "world";
	std::cout << v_3_hello.front() << std::endl;
	std::cout << v_3_hello[1] << std::endl;
	std::cout << v_3_hello[2] << std::endl;
	std::cout << v_3_hello.back() << std::endl;
}


/*
** ================================ Capacity ================================ **
*/

static void capacity() {
	NS::vector<int>	v_int;
	std::cout << "cap:" << v_int.capacity() << ",size:" << v_int.size() << ",max_size:" << v_int.max_size() << ",empty:" << v_int.empty() << std::endl;

	NS::vector<float>	v_10float(10);
	std::cout << "cap:" << v_10float.capacity() << ",size:" << v_10float.size() << ",max_size:" << v_10float.max_size() << ",empty:" << v_10float.empty() << std::endl;

	std::string	hello("hello");
	NS::vector<std::string>	v_3_hello(3, hello);
	NS::vector<std::string>	v_3_hello_copy(v_3_hello);
	const NS::vector<std::string>	v_3_hello_copy_const(v_3_hello);
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
	std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
	}
	try {
		v_3_hello_copy.reserve(v_3_hello_copy.max_size());
	} catch (std::exception const &e) {
		std::cout << e.what() << std::endl;
		std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
	}
	try {
		v_3_hello_copy.reserve(v_3_hello_copy.max_size() + 1);
	} catch (std::exception const &e) {
		std::cout << e.what() << std::endl;
		std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
	}
	v_3_hello_copy.reserve(3);
	std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
	}


/*
** =============================== Operator= ================================ **
*/

static void	operator_eq() {
	std::string	hello("hello");
	NS::vector<std::string>	v_3_hello(3, hello);
	NS::vector<std::string>	v_3_hello_copy(v_3_hello);

	print_vector(v_3_hello_copy);
	v_3_hello_copy = v_3_hello;
	std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
	print_vector(v_3_hello_copy);

	const NS::vector<std::string>	v_3_hello_copy_const(v_3_hello);
	v_3_hello_copy = v_3_hello_copy_const;
	std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
	print_vector(v_3_hello_copy);
}


/*
** =============================== Iterators ================================ **
*/

static void iterators() {
	int	arr[] = {0, 2, 4, 8};
	NS::vector<int>	v(arr, arr + sizeof(arr) / sizeof(arr[0]));
	NS::vector<int>::iterator	it;

	for (NS::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << std::endl;

	std::string	hello("hello");
	NS::vector<std::string>	v_3_hello(3, hello);
	NS::vector<std::string>	v2(v_3_hello.begin(), v_3_hello.end());
	print_vector(v2);
}

/*
** =============================== Modifiers ================================ **
*/

static void	modifiers() {
	std::string	arr[] = { "hello", "world", "42" };
	NS::vector<std::string>	vector_of_strings(arr, arr + sizeof(arr) / sizeof(arr[0]));

	// Clear
	{
		std::cout << "=== CLEAR ===" << std::endl;
		NS::vector<std::string> vec(vector_of_strings);
		std::cout << vec.size() << " " << vec.capacity() << std::endl;
		print_vector(vec);
		vec.clear();
		std::cout << vec.size() << " " << vec.capacity() << std::endl;
		print_vector(vec);
	}
	// Insert (1): iterator insert( iterator pos, const T& value );
	{
		std::cout << "=== INSERT 1 ===" << std::endl;
		NS::vector<std::string> vec(vector_of_strings);
		std::cout << *vec.insert(vec.begin(), "hi") << std::endl;
		std::cout << *vec.insert(vec.begin() + 2, "xx") << std::endl;
		print_vector(vec);;
	}
	// Insert (3): void insert( iterator pos, size_type count, const T& value );
	{
		std::cout << "=== INSERT 3 ===" << std::endl;
		NS::vector<std::string> vec(vector_of_strings);
		std::cout << vec.size() << " " << vec.capacity() << std::endl;
		vec.insert(vec.begin(), 1, "hi");
		vec.insert(vec.begin() + 2, 4, "xx");
		print_vector(vec);
		std::cout << vec.size() << " " << vec.capacity() << std::endl;
	}
	// Insert (4): void insert( iterator pos, InputIt first, InputIt last );
	{
		std::cout << "=== INSERT 4 ===" << std::endl;
		NS::vector<std::string> vec(vector_of_strings);
		std::deque<std::string>	m;
		m.push_back("hello"); m.push_back("world"); m.push_back("!");
		std::cout << vec.size() << " " << vec.capacity() << std::endl;
		vec.insert(vec.begin(), m.begin(), m.end());
		vec.insert(vec.begin() + 2, m.begin(), m.end());
		print_vector(vec);
		// std::cout << vec.size() << " " << vec.capacity() << std::endl; // capacity behaviour is not specified
	}
	// Erase (1)
	{
		std::string	arr[] = { "hello", "world", "42", "!" };
		NS::vector<std::string>	v(arr, arr + sizeof(arr) / sizeof(arr[0]));
		v.erase(v.begin() + 2);
		std::cout << v.size() << " " << v.capacity() << std::endl;
		print_vector(v);
		v.erase(v.begin());
		print_vector(v);
		std::cout << v.size() << " " << v.capacity() << std::endl;
		v.erase(v.end() - 1);
		print_vector(v);
		std::cout << v.size() << " " << v.capacity() << std::endl;
	}
	// Erase (2)
	{
		std::string	arr[] = { "hello", "world", "42", "!", "more", "words", "a", "b", "c", "d", "e" };
		NS::vector<std::string>	v(arr, arr + sizeof(arr) / sizeof(arr[0]));
		v.erase(v.begin(), v.begin());
		print_vector(v);
		std::cout << v.size() << " " << v.capacity() << std::endl;
		v.erase(v.end(), v.end());
		print_vector(v);
		std::cout << v.size() << " " << v.capacity() << std::endl;
		v.erase(v.begin(), v.begin() + 1);
		print_vector(v);
		std::cout << v.size() << " " << v.capacity() << std::endl;
		v.erase(v.begin() + 1, v.begin() + 4);
		print_vector(v);
		std::cout << v.size() << " " << v.capacity() << std::endl;
		v.erase(v.begin(), v.end());
		print_vector(v);
		std::cout << v.size() << " " << v.capacity() << std::endl;
	}
	// push_back
	{
		NS::vector<std::string> v;
		v.push_back("hello");
		v.push_back("world");
		v.push_back("!");
		print_vector(v);
		v.reserve(42);
		v.push_back("more");
		std::cout << v.size() << " " << v.capacity() << std::endl;
		print_vector(v);
	}
}

void	test_vector(void) {
	constructors();
	element_access();
	capacity();
	operator_eq();
	iterators();
	modifiers();
}
