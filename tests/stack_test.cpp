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
		std::cout << s.empty() << " " << s.size() << std::endl;
		s.push(2);
		std::cout << s.top() << " " << s.empty() << " " << s.size() << std::endl;
		s.push(6);
		std::cout << s.top() << " " << s.empty() << " " << s.size() << std::endl;
		s.push(51);
		std::cout << s.top() << " " << s.empty() << " " << s.size() << std::endl;
		s.pop();
		std::cout << s.top() << " " << s.empty() << " " << s.size() << std::endl;
		s.push(42);
		std::cout << s.top() << " " << s.empty() << " " << s.size() << std::endl;
		s.pop();
		std::cout << s.top() << " " << s.empty() << " " << s.size() << std::endl;
		s.pop();
		std::cout << s.top() << " " << s.empty() << " " << s.size() << std::endl;
		s.pop();
		std::cout << s.empty() << " " << s.size() << std::endl;
		s.push(42);
		std::cout << s.top() << " " << s.empty() << " " << s.size() << std::endl;
	}
}
