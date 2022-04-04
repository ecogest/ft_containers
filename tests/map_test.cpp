#include <map>
#include "AVLTree.hpp"

void	testAVLTree(void) {
	ft::AVLTree<std::string>	tree;
	// ft::AVLTree<int>	tree;

	// tree.insert(1);
	tree.insert("c");
	tree.insert("d");
	tree.insert("a");
	tree.insert("b");
	tree.print_infix();

}

void	test_map(void) {
	testAVLTree();
}
