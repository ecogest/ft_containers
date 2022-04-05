#include <map>
#include "AVLTree.hpp"

void	testAVLTree(void) {
	{
	ft::AVLTree<std::string>	tree;
	// ft::AVLTree<int>	tree;

	// tree.insert(1);
	tree.insert("c");
	tree.insert("d");
	tree.insert("a");
	tree.insert("b");
	tree.print_infix();
	}
	{
	ft::AVLTree<int>	tree;

	tree.insert(1);
	tree.insert(-1);
	tree.insert(-4);
	tree.insert(-2);
	tree.insert(32);
	tree.insert(12);
	tree.insert(42);
	tree.print_infix();
	}
}

void	test_map(void) {
	testAVLTree();
}
