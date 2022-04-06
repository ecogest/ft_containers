#include <map>
#include "AVLTree.hpp"
#include "pair.hpp"

#define Pair(X) ft::make_pair(X, 0)

void	testAVLTree(void) {
	{
		ft::AVLTree<ft::pair<std::string, int> >	tree;
		tree.insert(Pair("c"));
		tree.insert(Pair("d"));
		tree.insert(Pair("a"));
		tree.insert(Pair("b"));
		std::cout << "height: " << tree.height() << std::endl;
		std::cout << "-------------------" << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{
		ft::AVLTree<ft::pair<std::string, int> >	tree;
		tree.insert(Pair("a"));
		tree.insert(Pair("b"));
		tree.insert(Pair("c"));
		tree.insert(Pair("d"));
		tree.insert(Pair("e"));
		tree.insert(Pair("f"));
		tree.insert(Pair("g"));
		tree.insert(Pair("h"));
		tree.insert(Pair("i"));
		std::cout << "height: " << tree.height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{
		ft::AVLTree<ft::pair<std::string, int> >	tree;
		tree.insert(Pair("i"));
		tree.insert(Pair("h"));
		tree.insert(Pair("g"));
		tree.insert(Pair("f"));
		tree.insert(Pair("e"));
		tree.insert(Pair("d"));
		tree.insert(Pair("c"));
		tree.insert(Pair("b"));
		tree.insert(Pair("a"));
		std::cout << "height: " << tree.height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{
		ft::AVLTree<ft::pair<int, int> >	tree;
		tree.insert(Pair(1));
		tree.insert(Pair(-1));
		tree.insert(Pair(-4));
		tree.insert(Pair(-2));
		tree.insert(Pair(32));
		tree.insert(Pair(12));
		tree.insert(Pair(42));
		std::cout << "height: " << tree.height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
	{
		ft::AVLTree<ft::pair<int, int> >	tree;
		tree.insert(Pair(1000));
		tree.insert(Pair(-1000));
		tree.insert(Pair(-4000));
		tree.insert(Pair(-2000));
		tree.insert(Pair(32000));
		tree.insert(Pair(12000));
		tree.insert(Pair(42000));
		tree.insert(Pair(42));
		tree.insert(Pair(42));
		tree.insert(Pair(42));
		std::cout << "height: " << tree.height() << std::endl;
		tree.print_infix();
		tree.print_2d();
		std::cout << "-------------------" << std::endl;
	}
}

void	test_map(void) {
	testAVLTree();
}
