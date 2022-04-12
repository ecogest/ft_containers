#include "tests.hpp"
#include "stack.hpp"
#include <stack>

void test_stack() {
	{ // constructors
		NS::stack<int>	s;
		NS::stack<int>	t(s);
	}
	{ // push and top
		NS::stack<int> s;
		s.push(2);
		std::cout << s.top() << std::endl;
		s.push(6);
		std::cout << s.top() << std::endl;
		s.push(51);
		std::cout << s.top() << std::endl;
	}
}
