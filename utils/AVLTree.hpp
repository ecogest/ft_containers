/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVLTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:09:49 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/05 13:43:10 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVLTREE_HPP
# define AVLTREE_HPP

# include <string> // TODO: Remove
# include <iostream>
# include <sstream>
# include "vector.hpp"

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
	void	print_2d(void) const {
		if (_head) {
			ft::vector<std::string> output_vector;
			_print_2d(_head, output_vector, 0);
			for (size_t i = 0; i < output_vector.size(); i++)
				std::cout << output_vector[i] << std::endl;
		}
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
	static size_t	utf8_len(std::string s) {
		size_t	i = 0;
		size_t len = 0;
		unsigned char c;
		while ((c = s[i])) {
			if (c <= 0x7F)
				i++;
			else if (c <= 0xDF)
				i += 2;
			else if (c <= 0xEF)
				i += 3;
			else
				i += 4;
			len++;
		}
		return (len);
	}
	void	_print_2d(Node *node, ft::vector<std::string> &v, size_t level) const {
		if (!node)
			return ;
		std::string	left_padding(" ");
		std::string data(node->data);

		if (v.size() == level)
			v.push_back("");
		_print_2d(node->left, v, level + 1);
		if ((!node->parent || node == node->parent->left) && level + 1 < v.size())
			left_padding = std::string(utf8_len(v[level + 1])  - utf8_len(v[level]), ' ');
		else
			left_padding = std::string(utf8_len(v[level - 1])  - utf8_len(v[level]), ' ');
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
