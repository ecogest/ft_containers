/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVLTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:09:49 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/04 19:31:56 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVLTREE_HPP
# define AVLTREE_HPP

# include <string> // TODO: Remove
# include <iostream>

namespace ft {

template <class Data>
struct AVLNode {
	typedef AVLNode	Node;

	Data		_data;
	Node		*_left;
	Node		*_right;
	Node		*_parent;

	AVLNode(void): _data(), _left(NULL), _right(NULL) { }
	AVLNode(const Data &data): _data(data), _left(NULL), _right(NULL) { }
	AVLNode(Node const &copy): _data(), _left(copy._left), _right(copy._right) { }
	Node	&operator=(Node const &copy) {
		if (this == &copy)
			return (*this);
		_data = copy._data;
		_left = copy._left;
		_right = copy._right;
		return (*this);
	}
	virtual ~AVLNode() { }

	void	insert(Data const &data) {
		Node	**anode = NULL;
		Node	*node = this;
		Node	*parent = NULL;

		while (node) {
			parent = node;
			if (data < node->_data)
				anode = &node->_left;
			else
				anode = &node->_right;
			node = *anode;
		}
		*anode = new Node(data);
		(*anode)->_parent = parent;
	}
};

template <class Data>
class AVLTree {
public:

	typedef AVLNode<Data>	Node;

	//CANONICAL FORM ///////////////////////////////////////////////////////////
	//
	AVLTree(void): _head(NULL) { }
	AVLTree(AVLTree const &copy): _head(copy.head) { }
	AVLTree	&operator=(AVLTree const &copy) {
		if (this == &copy)
			return (*this);
		_head = copy._head;
	}
	virtual ~AVLTree(void) { }

	void		print_infix(void) const {
		if (_head)
			_print_infix_recurse(_head);
	}

	void	insert(Data const &data) {
		if (!_head)
			_head = new Node(data);
		else
			_head->insert(data);
	}

private:

	void	_print_infix_recurse(Node *node) const {
		if (!node)
			return ;
		_print_infix_recurse(node->_left);
		std::cout << node->_data << std::endl;
		_print_infix_recurse(node->_right);
	}

	// ATTRIBUTES //////////////////////////////////////////////////////////////
	Node	*_head;
};

}
#endif
