/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVLTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:09:49 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/07 11:03:47 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVLTREE_HPP
# define AVLTREE_HPP

# include <string> // TODO: Remove
# include <iostream>
# include <sstream>
# include "vector.hpp"
# include <algorithm>
# include "pair.hpp"

namespace ft {

// template <class Pair, class Compare = std::less<typename Pair::first_type> >
template <class Data, class Compare = std::less<Data> >
class AVLTree {

	struct AVLNode {
		typedef AVLNode	Node;

		Data		data;
		Node		*left;
		Node		*right;
		Node		*parent;

		AVLNode(void): data(), left(NULL), right(NULL), parent(NULL) { }
		AVLNode(const Data &data): data(data), left(NULL), right(NULL), parent(NULL) { }
		AVLNode(Node const &copy): data(copy.data), left(copy.left), right(copy.right), parent(copy.parent) { }
		Node	&operator=(Node const &copy) {
			if (this == &copy)
				return (*this);
			data = copy.data;
			left = copy.left;
			right = copy.right;
			parent = copy.parent;
			return (*this);
		}
		virtual ~AVLNode() { }
	};

public:

	typedef AVLNode	Node;
	typedef Data	value_type;
	typedef Compare	value_compare;

	// CANONICAL FORM //////////////////////////////////////////////////////////
	//
	AVLTree(void): _head(NULL) { }
	AVLTree(AVLTree const &copy): _head(copy.head) { }
	AVLTree	&operator=(AVLTree const &copy) {
		if (this == &copy)
			return (*this);
		_head = copy._head;
		return (*this);
	}
	virtual ~AVLTree(void) { }

	// METHODS /////////////////////////////////////////////////////////////////
	void		print_infix(void) const {
		if (_head)
			_print_infix(_head);
		std::cout << std::endl;
	}
	void	print_2d(void) const {
		if (_head) {
			ft::vector<std::string> output_vector;
			_print_2d(_head, output_vector, 0);
			std::cout << std::endl;
			for (size_t i = 0; i < output_vector.size(); i++)
				std::cout << output_vector[i] << std::endl;
		}
	}

	size_t	height(void) {
		return(height(_head));
	}
	size_t	height(Node *node) {
		if (!node)
			return (0);
		return (1 + std::max(height(node->left), height(node->right)));
	}

	Node	**get_node_root(Node *node) {
		Node	**root;
		if (node == _head)
			root = &_head;
		else if (node == node->parent->left)
			root = &node->parent->left;
		else
			root = &node->parent->right;
		return (root);
	}
	// Right son takes place of the node
	Node	*left_rotate(Node *node) {
		Node	**root = get_node_root(node);
		*root = node->right;
		node->right = (*root)->left;
		(*root)->left = node;
		(*root)->parent = node->parent;
		node->parent = (*root);
		return (*root);
	}
	// Left son takes place of the node
	Node	*right_rotate(Node *node) {
		Node	**root = get_node_root(node);
		*root = node->left;
		node->left = (*root)->right;
		(*root)->right = node;
		(*root)->parent = node->parent;
		node->parent = (*root);
		return (*root);
	}
	void	balance(Node *node) {
		// RIGHT IMBALANCE / LEFT ROTATION
		if (height(node->right) > height(node->left) + 1 && height(node->right->right) >= height(node->right->left))
			node = left_rotate(node);
		// LEFT IMBALANCE / RIGHT ROTATION
		else if (height(node->left) > height(node->right) + 1 && height(node->left->left) >= height(node->left->right))
			node = right_rotate(node);
		// RL IMBALANCE / RL ROTATION
		else if (height(node->right) > height(node->left) + 1 && height(node->right->right) < height(node->right->left)) {
			right_rotate(node->right);
			node = left_rotate(node);
		}
		// LR IMBALANCE / LR ROTATION
		else if (height(node->left) > height(node->right) + 1 && height(node->left->left) < height(node->left->right)) {
			left_rotate(node->left);
			node = right_rotate(node);
		}

		if (node->parent)
			balance(node->parent);
	}
	void	insert(value_type const &data) {
		if (!_head)
			_head = new Node(data);
		else {
			Node	*node = _head;
			Node	*parent = NULL;
			Node	**anode = NULL;
			value_compare	comp;
			while (node) {
				parent = node;
				if (comp(data, node->data))
					anode = &node->left;
				else
					anode = &node->right;
				node = *anode;
			}
			*anode = new Node(data);
			(*anode)->parent = parent;
			if (parent->parent)
				balance(parent->parent);
		}
	}

	private:

	// PRIVATE METHODS /////////////////////////////////////////////////////////
	void	_print_infix(Node *node) const {
		if (!node)
			return ;
		_print_infix(node->left);
		std::cout << "[" << node->data << "]  ";
		_print_infix(node->right);
	}
	static size_t	_utf8_len(std::string s) {
		size_t	i = 0, len = 0;
		unsigned char c;
		while ((c = s[i])) {
			i += 1 + (c > 0x7F) + (c > 0xDF) + (c > 0xEF);
			len++;
		}
		return (len);
	}
	static bool _utf8_cmp(std::string a, std::string b) {
		return _utf8_len(a) < _utf8_len(b);
	}
	void	_print_2d(Node *node, ft::vector<std::string> &v, size_t level) const {
		if (!node)
			return ;
		std::string	left_padding(" ");
		std::ostringstream	oss;
		oss << '|' << node->data << '|';
		std::string data(oss.str());

		if (v.size() == level)
			v.push_back("");
		_print_2d(node->left, v, level + 1);
		left_padding = std::string(_utf8_len(*std::max_element(v.begin(), v.end(), _utf8_cmp))  - _utf8_len(v[level]), ' ');
		if (node->right)
			data = data + "⬎";
		if (node->left)
			data = std::string("⬐") + data;
		v[level] = v[level] + left_padding + data;
		_print_2d(node->right, v, level + 1);
	}

	// ATTRIBUTES //////////////////////////////////////////////////////////////
	Node	*_head;
};

}
#endif
