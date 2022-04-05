/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVLTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:09:49 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/05 10:37:23 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVLTREE_HPP
# define AVLTREE_HPP

# include <string> // TODO: Remove
# include <iostream>

namespace ft {

template <class Data>
class AVLTree {

	struct AVLNode {
		typedef AVLNode	Node;

		Data		data;
		Node		*left;
		Node		*right;
		Node		*parent;

		AVLNode(void): data(), left(NULL), right(NULL) { }
		AVLNode(const Data &data): data(data), left(NULL), right(NULL) { }
		AVLNode(Node const &copy): data(), left(copy.left), right(copy.right) { }
		Node	&operator=(Node const &copy) {
			if (this == &copy)
				return (*this);
			data = copy.data;
			left = copy.left;
			right = copy.right;
			return (*this);
		}
		virtual ~AVLNode() { }
	};

public:

	typedef AVLNode	Node;

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
	}

	void	insert(Data const &data) {
		if (!_head)
			_head = new Node(data);
		else {
			Node	*node = _head;
			Node	*parent = NULL;
			Node	**anode = NULL;
			while (node) {
				parent = node;
				if (data < node->data)
					anode = &node->left;
				else
					anode = &node->right;
				node = *anode;
			}
			*anode = new Node(data);
			(*anode)->parent = parent;
		}
	}

	private:

	// PRIVATE METHODS /////////////////////////////////////////////////////////
	void	_print_infix(Node *node) const {
		if (!node)
			return ;
		_print_infix(node->left);
		std::cout << node->data << std::endl;
		_print_infix(node->right);
	}

	// ATTRIBUTES //////////////////////////////////////////////////////////////
	Node	*_head;
};

}
#endif
