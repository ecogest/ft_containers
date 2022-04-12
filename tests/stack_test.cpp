#include "tests.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include <stack>
#include <vector>

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
	{ // relational operators
		NS::stack<char, NS::vector<char> > abc;
		abc.push('a'); abc.push('b'); abc.push('c');
		NS::stack<char, NS::vector<char> > abc2(abc);
		abc2.push('a'); abc2.push('b'); abc2.push('c');
		NS::stack<char, NS::vector<char> > bob;
		bob.push('b'); bob.push('o'); bob.push('b'); bob.push('b');
		// Compare non equal containers
		std::cout << "abc == bob returns " << (abc == bob) << '\n';
		std::cout << "abc != bob returns " << (abc != bob) << '\n';
		std::cout << "abc <  bob returns " << (abc < bob) << '\n';
		std::cout << "abc <= bob returns " << (abc <= bob) << '\n';
		std::cout << "abc >  bob returns " << (abc > bob) << '\n';
		std::cout << "abc >= bob returns " << (abc >= bob) << '\n';

		std::cout << '\n';

		// Compare equal containers
		std::cout << "abc == abc2 returns " << (abc == abc2) << '\n';
		std::cout << "abc != abc2 returns " << (abc != abc2) << '\n';
		std::cout << "abc <  abc2 returns " << (abc < abc2) << '\n';
		std::cout << "abc <= abc2 returns " << (abc <= abc2) << '\n';
		std::cout << "abc >  abc2 returns " << (abc > abc2) << '\n';
		std::cout << "abc >= abc2 returns " << (abc >= abc2) << '\n';
	}
}
