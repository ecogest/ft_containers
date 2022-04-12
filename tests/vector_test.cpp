#include "tests.hpp"

#include "vector.hpp"
#include <vector>

#include <string>

#include "lexicographical_compare.hpp"

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

void constructors() {
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

	// assign, operator =
	{
		std::string	arr[] = { "hello", "world", "42", "!" };
		NS::vector<std::string>	v(arr, arr + sizeof(arr) / sizeof(arr[0]));
		std::string	arr2[] = { "xx", "pp" };
		NS::vector<std::string>	v2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
		v2.assign(v.begin(), v.end());
		print_vector(v2);
		NS::vector<std::string> v3;
		v3.assign(4, "helloworld");
		print_vector(v3);
		v3 = v;
		print_vector(v3);
	}
}


/*
** ============================= Element access ============================= **
*/

void element_access() {
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

void capacity() {
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
	// works all right but valgrind does not like (even with std::)
	// try {
	// 	v_3_hello_copy.reserve(v_3_hello_copy.max_size() - 1);
	// } catch (std::exception const &e) {
	// 	std::cout << e.what() << std::endl;
	// std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
	// }
	// try {
	// 	v_3_hello_copy.reserve(v_3_hello_copy.max_size());
	// } catch (std::exception const &e) {
	// 	std::cout << e.what() << std::endl;
	// 	std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
	// }
	// try {
	// 	v_3_hello_copy.reserve(v_3_hello_copy.max_size() + 1);
	// } catch (std::exception const &e) {
	// 	std::cout << e.what() << std::endl;
	// 	std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
	// }
	v_3_hello_copy.reserve(3);
	std::cout << "cap:" << v_3_hello_copy.capacity() << ",size:" << v_3_hello_copy.size() << ",max_size:" << v_3_hello_copy.max_size() << ",empty:" << v_3_hello_copy.empty() << std::endl;
}


/*
** =============================== Operator= ================================ **
*/

void	operator_eq() {
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

void iterators() {
	{
		int	arr[] = {0, 2, 4, 8};
		NS::vector<int>	v(arr, arr + sizeof(arr) / sizeof(arr[0]));

		for (NS::vector<int>::iterator it = v.begin(); it != v.end(); it++)
			std::cout << *it << std::endl;

		for (NS::vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
			std::cout << *it << std::endl;

		NS::vector<int>::iterator it = v.begin();
		NS::vector<int>::const_iterator it_const = it;
		std::cout << (it == it) << " " << (it_const == it_const) << std::endl;
		std::cout << (it == it_const) << " " << (it_const == it) << std::endl;
		std::cout << (it != it) << " " << (it_const != it_const) << std::endl;
		std::cout << (it != it_const) << " " << (it_const != it) << std::endl;
		std::cout << (it <= it) << std::endl;
		std::cout << (it <= it_const) << std::endl;
		std::cout << (it < it) << std::endl;
		std::cout << (it < it_const) << std::endl;
		std::cout << *(it + 2) << std::endl;
		std::cout << *(it_const + 2) << std::endl;
		std::cout << *(it_const + 2) << std::endl;
		it++;
		std::cout << (it == it) << " " << (it_const == it_const) << std::endl;
		std::cout << (it == it_const) << " " << (it_const == it) << std::endl;
		std::cout << (it != it) << " " << (it_const != it_const) << std::endl;
		std::cout << (it != it_const) << " " << (it_const != it) << std::endl;
		std::cout << (it <= it) << std::endl;
		std::cout << (it <= it_const) << std::endl;
		std::cout << (it < it) << std::endl;
		std::cout << (it < it_const) << std::endl;
		std::cout << (it >= it) << std::endl;
		std::cout << (it >= it_const) << std::endl;
		std::cout << (it > it) << std::endl;
		std::cout << (it > it_const) << std::endl;
		it_const++;
		std::cout << it[0] << " " << it_const[0] << std::endl;
		std::cout << it[1] << " " << it_const[1] << std::endl;
		it--;
		it_const--;
		std::cout << it[0] << " " << it_const[0] << std::endl;
		std::cout << it[1] << " " << it_const[1] << std::endl;
		std::cout << (it - (it + 1)) << std::endl;
		std::cout << ((it + 1) - it) << std::endl;

		// THIS SHOULD NOT COMPILE (const_iterator -> iterator)
		// NS::vector<int>::const_iterator it_const = v.begin();
		// NS::vector<int>::iterator it = it_const;
		// (void)it;

		// operator-
		std::cout << (v.begin() - v.end()) << " " << (v.end() - v.begin()) << std::endl;
		// operator of comparison
		std::cout << (v.begin() == v.begin()) << " " << (v.begin() != v.begin()) << std::endl;
		std::cout << (v.begin() == v.end()) << " " << (v.end() != v.begin()) << std::endl;
		std::cout << (v.begin() < v.end()) << " " << (v.end() < v.begin()) << std::endl;
		std::cout << (v.begin() > v.end()) << " " << (v.end() > v.begin()) << std::endl;
		std::cout << (v.begin() <= v.end()) << " " << (v.end() <= v.begin()) << std::endl;
		std::cout << (v.begin() >= v.end()) << " " << (v.end() >= v.begin()) << std::endl;

		std::string	hello("hello");
		NS::vector<std::string>	v_3_hello(3, hello);
		NS::vector<std::string>	v2(v_3_hello.begin(), v_3_hello.end());
		print_vector(v2);
		// operator->
		std::cout << (v_3_hello.begin())->length() << std::endl;
	}
	{
		// reverse_iterator
		int	arr[] = {0, 2, 4, 8};
		NS::vector<int>	v(arr, arr + sizeof(arr) / sizeof(arr[0]));
		for (NS::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); it++)
			std::cout << *it << std::endl;
		for (NS::vector<int>::const_reverse_iterator it = v.rbegin(); it != v.rend(); it++)
			std::cout << *it << std::endl;
		NS::reverse_iterator<NS::vector<int>::iterator> it(v.end());
		it++;
		std::cout << *it << std::endl;
		it++;
		std::cout << it[1] << std::endl;
		it--;
		std::cout << *(it + 1) << std::endl;
		std::cout << (it <= it + 1) << std::endl;
		std::cout << (it < it + 1) << std::endl;
		std::cout << (it > it + 1) << std::endl;
		std::cout << (it >= it + 1) << std::endl;
		std::cout << (it == it + 1) << std::endl;
		std::cout << (it != it + 1) << std::endl;
		std::cout << (it <= it) << std::endl;
		std::cout << (it < it) << std::endl;
		std::cout << (it > it) << std::endl;
		std::cout << (it >= it) << std::endl;
		std::cout << (it == it) << std::endl;
		std::cout << (it != it) << std::endl;
		std::cout << (it - (it + 1)) << std::endl;
		std::cout << ((it + 1) - it) << std::endl;
	}
}

/*
** =============================== Modifiers ================================ **
*/

void	modifiers() {
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
		std::cout << vec.size() << std::endl;
		// std::cout << vec.size() << " " << vec.capacity() << std::endl;  // capacity behaviour is implementation dependant
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
	// push_back - pop_back
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
		v.pop_back();
		print_vector(v);
		v.pop_back();
		v.pop_back();
		print_vector(v);
	}
	// resize
	{
		std::string	arr[] = { "hello", "world", "42", "!", "more", "words", "a", "b", "c", "d", "e" };
		NS::vector<std::string>	v(arr, arr + sizeof(arr) / sizeof(arr[0]));
		v.resize(v.size());
		print_vector(v);
		v.resize(v.size() + 3);
		print_vector(v);
		v.resize(v.size() + 2, "heelllo");
		print_vector(v);
		v.resize(v.size() - 2, "heelllo");
		print_vector(v);
		v.resize(0);
		print_vector(v);
		v.resize(1, "end");
		print_vector(v);
	}
	// swap
	{
		std::string	arr[] = { "hello", "world", "42", "!" };
		NS::vector<std::string>	v(arr, arr + sizeof(arr) / sizeof(arr[0]));
		std::string	arr2[] = { "xx", "pp" };
		NS::vector<std::string>	v2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
		typedef NS::vector<std::string>::iterator	iterator;
		iterator vbegin_before = v.begin();
		iterator v2begin_before = v2.begin();
		v.swap(v2);
		iterator vbegin_after = v.begin();
		iterator v2begin_after = v2.begin();
		print_vector(v);
		std::cout << (vbegin_before == v2begin_after) << std::endl;
		std::cout << (v2begin_before == vbegin_after) << std::endl;
		std::cout << v.size() << " " << v.capacity() << std::endl;
		print_vector(v2);
		std::cout << v2.size() << " " << v2.capacity() << std::endl;
		NS::swap(v, v2);
		print_vector(v);
		std::cout << v.size() << " " << v.capacity() << std::endl;
		print_vector(v2);
		std::cout << v2.size() << " " << v2.capacity() << std::endl;
	}
}

void	non_member() {
	// operator==, !=
	{
		std::string	arr[] = { "hello", "world", "42", "!" };
		NS::vector<std::string>	v(arr, arr + sizeof(arr) / sizeof(arr[0]));
		std::string	arr2[] = { "xx", "pp" };
		NS::vector<std::string>	v2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
		NS::vector<std::string>	v3(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
		std::cout << (v == v2) << " " << (v2 == v3) << std::endl;
		std::cout << (v != v2) << " " << (v2 != v3) << std::endl;
		v.clear(); v2.clear();
		std::cout << (v == v2) << " " << (v2 == v3) << std::endl;
		std::cout << (v != v2) << " " << (v2 != v3) << std::endl;
	}
	// operators <, >, <=, >=
	{
		NS::vector<std::string> v1;
		NS::vector<std::string> v2;
		std::cout << (v1 < v2) << (v1 > v2) << (v1 <= v2) << (v1 >= v2) << std::endl;
		v1.push_back("hello");
		std::cout << (v1 < v2) << (v1 > v2) << (v1 <= v2) << (v1 >= v2) << std::endl;
		v2.push_back("hello");
		std::cout << (v1 < v2) << (v1 > v2) << (v1 <= v2) << (v1 >= v2) << std::endl;
		v1.push_back("world");
		std::cout << (v1 < v2) << (v1 > v2) << (v1 <= v2) << (v1 >= v2) << std::endl;
		v2.push_back("wOrld");
		std::cout << (v1 < v2) << (v1 > v2) << (v1 <= v2) << (v1 >= v2) << std::endl;
		v2.pop_back();
		v2.push_back("world");
		std::cout << (v1 < v2) << (v1 > v2) << (v1 <= v2) << (v1 >= v2) << std::endl;
		v2.push_back("!");
		std::cout << (v1 < v2) << (v1 > v2) << (v1 <= v2) << (v1 >= v2) << std::endl;
	}
	// lexicographical_compare (3)
	{
		bool (*comp)(std::string const &, std::string const &) = std::operator<;
		NS::vector<std::string> v1;
		NS::vector<std::string> v2;
		std::cout << NS::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), comp) << std::endl;
		v1.push_back("hello");
		std::cout << NS::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), comp) << std::endl;
		v2.push_back("hello");
		std::cout << NS::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), comp) << std::endl;
		v1.push_back("world");
		std::cout << NS::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), comp) << std::endl;
		v2.push_back("wOrld");
		std::cout << NS::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), comp) << std::endl;
		v2.pop_back();
		v2.push_back("world");
		std::cout << NS::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), comp) << std::endl;
		v2.push_back("!");
		std::cout << NS::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), comp) << std::endl;
	}
}

void	more_tests() {
	{ // assign-insert special case
		NS::vector<int> vct(7);
		NS::vector<int> vct_two(4);
		NS::vector<int> vct_three;
		NS::vector<int> vct_four;

		for (unsigned long int i = 0; i < vct.size(); ++i)
			vct[i] = (vct.size() - i) * 3;
		for (unsigned long int i = 0; i < vct_two.size(); ++i)
			vct_two[i] = (vct_two.size() - i) * 5;
		print_vector(vct);
		print_vector(vct_two);

		vct_three.assign(vct.begin(), vct.end());
		vct.assign(vct_two.begin(), vct_two.end());
		vct_two.assign(2, 42);
		vct_four.assign(4, 21);

		std::cout << "\t### After assign(): ###" << std::endl;
	}
	{ // iterators
		const int size = 5;
		NS::vector<int> vct(size);
		NS::vector<int>::reverse_iterator it = vct.rbegin();
		NS::vector<int>::const_reverse_iterator ite = vct.rbegin();

		for (int i = 0; i < size; ++i)
			it[i] = (size - i) * 5;

		it = it + 5;
		it = 1 + it;
		it = it - 4;
		std::cout << *(it += 2) << std::endl;
		std::cout << *(it -= 1) << std::endl;

		*(it -= 2) = 42;
		*(it += 2) = 21;

		std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

		std::cout << "(it == const_it): " << (ite == it) << std::endl;
		std::cout << "(const_ite - it): " << (ite - it) << std::endl;
		std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	}
}

void	test_vector(void) {
	constructors();
	element_access();
	capacity();
	operator_eq();
	iterators();
	modifiers();
	non_member();
	more_tests();
}
