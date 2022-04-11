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
	{ // find, count
		std::cout << *M.find(0) << std::endl;
		std::cout << M.count(0) << std::endl;
		std::cout << *M.find(1) << std::endl;
		std::cout << *M.find(2) << std::endl;
		std::cout << *M.find(7) << std::endl;
		std::cout << M.count(7) << std::endl;
		(*M.find(7)).second = "AAA";
		std::cout << *M.find(7) << std::endl;
		if (M.find(42) != M.end())
			std::cout << *M.find(42) << std::endl;
		else
			std::cout << "NOT FOUND" << std::endl;
		std::cout << M.count(42) << std::endl;
		std::cout << M.count(1) << std::endl;
		M.erase(1);
		std::cout << M.count(1) << std::endl;
		M[1] = "BACK";
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
	{ // insert
		NS::map<size_t, std::string> N(M);
		NS::pair<NS::map<size_t, std::string>::iterator, bool> result = N.insert(NS::make_pair<size_t, std::string>(42, "yo"));
		std::cout << std::boolalpha;
		std::cout << "(" << *result.first << ", " << result.second << ")" << std::endl;
		result = N.insert(NS::make_pair<size_t, std::string>(42, "lo"));
		std::cout << "(" << *result.first << ", " << result.second << ")" << std::endl;
		for (NS::map<size_t, std::string>::const_iterator it = N.begin(); it != N.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		for (size_t i = 0; i <= 12; i++) {
			result = N.insert(NS::make_pair<size_t, std::string>(i, "INSERT"));
			std::cout << "(" << *result.first << ", " << result.second << ")" << std::endl;
		}
		for (NS::map<size_t, std::string>::iterator it = N.begin(); it != N.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	{ // insert (from scratch)
		NS::map<size_t, std::string> N;
		NS::pair<NS::map<size_t, std::string>::iterator, bool> result = N.insert(NS::make_pair<size_t, std::string>(42, "yo"));
		std::cout << "(" << *result.first << ", " << result.second << ")" << std::endl;
		N.clear();
		result = N.insert(NS::make_pair<size_t, std::string>(42, "lo"));
		std::cout << "(" << *result.first << ", " << result.second << ")" << std::endl;
		result = N.insert(NS::make_pair<size_t, std::string>(42, "lo"));
		std::cout << "(" << *result.first << ", " << result.second << ")" << std::endl;
	}
	{ // operator[]
		NS::map<size_t, std::string> N;
		std::cout << (N[42] = "!") << std::endl;
		std::cout << (N[2] = "hello") << std::endl;
		std::cout << (N[12] = "tada") << std::endl;
		std::cout << (N[12] = "world") << std::endl;
		std::cout << (N[42] = "!!") << std::endl;
		for (NS::map<size_t, std::string>::const_iterator it = N.begin(); it != N.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	{ // size(), max_size(), empty()
		NS::map<size_t, std::string> N;
		for (size_t i = 0; i < 12; i++) {
			N[i] = "hello";
			std::cout << N.size() << " ";
		}
		std::cout << std::endl;
		std::cout << N.max_size() << std::endl;;
		std::cout << N.empty() << std::endl;;
		N.clear();
		std::cout << N.size() << std::endl;;
		std::cout << N.empty() << std::endl;;
		std::cout << N.max_size() << std::endl;;
		for (size_t i = 0; i < 12; i++) { N[i] = "hello"; }
		std::cout << N.size() << std::endl;;
		for (size_t i = 0; i < 12; i++) {
			N.erase(i);
			std::cout << N.size() << " ";
		}
		std::cout << std::endl;
	}
	{ // erase
		NS::map<size_t, std::string> N;
		for (size_t i = 0; i < 12; i++)
			N[i] = "hello";
		N.erase(++(N.begin()), --(N.end()));
		for (NS::map<size_t, std::string>::const_iterator it = N.begin(); it != N.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		N.erase(N.begin(), N.end());
		for (NS::map<size_t, std::string>::const_iterator it = N.begin(); it != N.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		for (size_t i = 0; i < 12; i++)
			N[i] = "hello";
		std::cout << N.erase(7) << std::endl;
		std::cout << N.erase(0) << std::endl;
		for (NS::map<size_t, std::string>::const_iterator it = N.begin(); it != N.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << N.erase(0) << std::endl;
		N.erase(--(N.end()));
		N.erase(N.begin());
		for (NS::map<size_t, std::string>::const_iterator it = N.begin(); it != N.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	{ // bounds
		NS::map<size_t, std::string> N;
		for (size_t i = 0; i < 5; i+=2)
			N[i] = "hello";
		if (N.lower_bound(0) != N.end()) std::cout << *N.lower_bound(0) << " "; else std::cout << "X" << " ";
		if (N.lower_bound(1) != N.end()) std::cout << *N.lower_bound(1) << " "; else std::cout << "X" << " ";
		if (N.lower_bound(2) != N.end()) std::cout << *N.lower_bound(2) << " "; else std::cout << "X" << " ";
		if (N.lower_bound(3) != N.end()) std::cout << *N.lower_bound(3) << " "; else std::cout << "X" << " ";
		if (N.lower_bound(4) != N.end()) std::cout << *N.lower_bound(4) << " "; else std::cout << "X" << " ";
		if (N.lower_bound(5) != N.end()) std::cout << *N.lower_bound(5) << " "; else std::cout << "X" << " ";
		if (N.lower_bound(6) != N.end()) std::cout << *N.lower_bound(6) << " "; else std::cout << "X" << " ";
		if (N.lower_bound(7) != N.end()) std::cout << *N.lower_bound(7) << " "; else std::cout << "X" << " ";
		if (N.lower_bound(8) != N.end()) std::cout << *N.lower_bound(8) << " "; else std::cout << "X" << " ";
		if (N.lower_bound(9) != N.end()) std::cout << *N.lower_bound(9) << " "; else std::cout << "X" << " ";
		std::cout << std::endl;
		NS::map<size_t, std::string> const P(N);
		if (P.lower_bound(0) != P.end()) std::cout << *P.lower_bound(0) << " "; else std::cout << "X" << " ";
		if (P.lower_bound(1) != P.end()) std::cout << *P.lower_bound(1) << " "; else std::cout << "X" << " ";
		if (P.lower_bound(2) != P.end()) std::cout << *P.lower_bound(2) << " "; else std::cout << "X" << " ";
		if (P.lower_bound(3) != P.end()) std::cout << *P.lower_bound(3) << " "; else std::cout << "X" << " ";
		if (P.lower_bound(4) != P.end()) std::cout << *P.lower_bound(4) << " "; else std::cout << "X" << " ";
		if (P.lower_bound(5) != P.end()) std::cout << *P.lower_bound(5) << " "; else std::cout << "X" << " ";
		if (P.lower_bound(6) != P.end()) std::cout << *P.lower_bound(6) << " "; else std::cout << "X" << " ";
		if (P.lower_bound(7) != P.end()) std::cout << *P.lower_bound(7) << " "; else std::cout << "X" << " ";
		if (P.lower_bound(8) != P.end()) std::cout << *P.lower_bound(8) << " "; else std::cout << "X" << " ";
		if (P.lower_bound(9) != P.end()) std::cout << *P.lower_bound(9) << " "; else std::cout << "X" << " ";
		std::cout << std::endl;
		if (N.upper_bound(0) != N.end()) std::cout << *N.upper_bound(0) << " "; else std::cout << "X" << " ";
		if (N.upper_bound(1) != N.end()) std::cout << *N.upper_bound(1) << " "; else std::cout << "X" << " ";
		if (N.upper_bound(2) != N.end()) std::cout << *N.upper_bound(2) << " "; else std::cout << "X" << " ";
		if (N.upper_bound(3) != N.end()) std::cout << *N.upper_bound(3) << " "; else std::cout << "X" << " ";
		if (N.upper_bound(4) != N.end()) std::cout << *N.upper_bound(4) << " "; else std::cout << "X" << " ";
		if (N.upper_bound(5) != N.end()) std::cout << *N.upper_bound(5) << " "; else std::cout << "X" << " ";
		if (N.upper_bound(6) != N.end()) std::cout << *N.upper_bound(6) << " "; else std::cout << "X" << " ";
		if (N.upper_bound(7) != N.end()) std::cout << *N.upper_bound(7) << " "; else std::cout << "X" << " ";
		if (N.upper_bound(8) != N.end()) std::cout << *N.upper_bound(8) << " "; else std::cout << "X" << " ";
		if (N.upper_bound(9) != N.end()) std::cout << *N.upper_bound(9) << " "; else std::cout << "X" << " ";
		std::cout << std::endl;
		if (P.upper_bound(0) != P.end()) std::cout << *P.upper_bound(0) << " "; else std::cout << "X" << " ";
		if (P.upper_bound(1) != P.end()) std::cout << *P.upper_bound(1) << " "; else std::cout << "X" << " ";
		if (P.upper_bound(2) != P.end()) std::cout << *P.upper_bound(2) << " "; else std::cout << "X" << " ";
		if (P.upper_bound(3) != P.end()) std::cout << *P.upper_bound(3) << " "; else std::cout << "X" << " ";
		if (P.upper_bound(4) != P.end()) std::cout << *P.upper_bound(4) << " "; else std::cout << "X" << " ";
		if (P.upper_bound(5) != P.end()) std::cout << *P.upper_bound(5) << " "; else std::cout << "X" << " ";
		if (P.upper_bound(6) != P.end()) std::cout << *P.upper_bound(6) << " "; else std::cout << "X" << " ";
		if (P.upper_bound(7) != P.end()) std::cout << *P.upper_bound(7) << " "; else std::cout << "X" << " ";
		if (P.upper_bound(8) != P.end()) std::cout << *P.upper_bound(8) << " "; else std::cout << "X" << " ";
		if (P.upper_bound(9) != P.end()) std::cout << *P.upper_bound(9) << " "; else std::cout << "X" << " ";
		std::cout << std::endl;
		typedef NS::map<size_t, std::string>::iterator iterator;
		std::cout << "--- Equal rage --- " << std::endl;
		NS::pair<iterator, iterator> p = N.equal_range(0);
		for (iterator it = p.first; it != p.second; it++) std::cout << *it << " "; std::cout << std::endl;
		p = N.equal_range(1);
		for (iterator it = p.first; it != p.second; it++) std::cout << *it << " "; std::cout << std::endl;
		p = N.equal_range(2);
		for (iterator it = p.first; it != p.second; it++) std::cout << *it << " "; std::cout << std::endl;
		p = N.equal_range(3);
		for (iterator it = p.first; it != p.second; it++) std::cout << *it << " "; std::cout << std::endl;
		p = N.equal_range(4);
		for (iterator it = p.first; it != p.second; it++) std::cout << *it << " "; std::cout << std::endl;
		p = N.equal_range(7);
		for (iterator it = p.first; it != p.second; it++) std::cout << *it << " "; std::cout << std::endl;
		p = N.equal_range(8);
		for (iterator it = p.first; it != p.second; it++) std::cout << *it << " "; std::cout << std::endl;
		p = N.equal_range(9);
		for (iterator it = p.first; it != p.second; it++) std::cout << *it << " "; std::cout << std::endl;
	}
	{ // swap
		NS::map<size_t, std::string> N;
		for (size_t i = 0; i < 5; i+=2)
			N[i] = "hello";
		NS::map<size_t, std::string> P;
		for (size_t i = 1; i < 5; i+=3)
			P[i] = "world";
		typedef NS::map<size_t, std::string>::iterator iterator;
		for (iterator it = N.begin(); it != N.end(); it++) std::cout << *it << " "; std::cout << std::endl;
		for (iterator it = P.begin(); it != P.end(); it++) std::cout << *it << " "; std::cout << std::endl;
		iterator nbegin_before = N.begin();
		iterator pbegin_before = P.begin();
		N.swap(P);
		iterator nbegin_after = N.begin();
		iterator pbegin_after = P.begin();
		for (iterator it = N.begin(); it != N.end(); it++) std::cout << *it << " "; std::cout << std::endl;
		for (iterator it = P.begin(); it != P.end(); it++) std::cout << *it << " "; std::cout << std::endl;
		std::cout << (nbegin_before == pbegin_after) << std::endl;
		std::cout << (pbegin_before == nbegin_after) << std::endl;
	}
}

// See avl_test for more details concerning the structure
void	test_map(void) {
	std::cout << "===================" << std::endl;
	std::cout << "====== MAP ========" << std::endl;
	std::cout << "===================" << std::endl;
	constructor_insert_and_iterator_test();
}
