/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVLTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:09:49 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/09 10:38:54 by mjacq            ###   ########.fr       */
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
template <class Data, class Compare = std::less<Data>, class Allocator = std::allocator<Data> >
class AVLTree {

public:
	typedef Data	value_type;
	typedef Compare	value_compare;
	typedef std::size_t                          	 size_type; // check type
	typedef std::ptrdiff_t                       	 difference_type; // check type
	typedef value_type&                          	 reference;
	typedef const value_type&                    	 const_reference;

private:
	struct AVLNode {
		typedef Data	value_type;
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
	}; // AVLNode

	template <class T>
	class AVLIterator {
public:
	typedef typename std::ptrdiff_t                  difference_type; // TODO: see if possible https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
	typedef typename T::value_type                   value_type;
	typedef value_type*                              pointer;
	typedef value_type&                              reference;
	typedef typename std::bidirectional_iterator_tag iterator_category;  // TODO: check if ft::random_access_iterator_tag is OK
private:
	typedef T	node_type;
	typedef T&	node_reference;
	typedef T*	node_pointer;
	node_pointer	_node;
public:
	AVLIterator(): _node(0)                                     { }
	AVLIterator(node_pointer ptr): _node(ptr)                        { }
	AVLIterator(AVLIterator const &it): _node(it.base())     { }

	operator AVLIterator<const T>() const { return AVLIterator<const T>(_node); }

	AVLIterator	&operator=(AVLIterator const &it) { _node = it._node; return (*this); }
	~AVLIterator()                                { }

	// [LegacyBidirectionalIterator] < LegacyForwardIterator
	AVLIterator	&operator--()   { _node = _prev(_node) ; return (*this); }
	AVLIterator	operator--(int) { AVLIterator tmp; tmp._node = _node; _node = _prev(_node); return (tmp); }

	// [LegacyForwardIterator] < LegacyIterator, LegacyInputOperator, DefaultConstructible
	AVLIterator	operator++(int) { AVLIterator tmp; tmp._node = _node; _node = _next(_node); return (tmp); }

	// [LegacyInputOperator] < (LegacyOperator), EquallyComparable
	bool			operator!=(AVLIterator<const T> const &rhs) const { return (_node != rhs.base()); }
	pointer			operator->() const                                   { return (&_node->data); }

	// [EquallyComparable]
	bool			operator==(AVLIterator<const T> const &rhs) const { return (_node == rhs.base()); }

	// [LegacyIterator]
	reference		operator*(void) const { return _node->data; }
	AVLIterator		&operator++()         { _node = _next(_node); return (*this); }

	// getter
	node_pointer	base(void) const     { return _node; }

private:
	node_pointer	_next(node_pointer node) {
		if (node->right) {
			node = node->right;
			while (node->left)
				node = node->left;
			return (node);
		}
		else {
			while (node->parent) {
				if (node == node->parent->right)
					node = node->parent;
				else
					return (node->parent);
			}
			return (NULL);
		}
	}
	node_pointer	_prev(node_pointer node) {
		if (node->left) {
			node = node->left;
			while (node->right)
				node = node->right;
			return (node);
		}
		else {
			while (node->parent) {
				if (node == node->parent->left)
					node = node->parent;
				else
					return (node->parent);
			}
			return (NULL);
		}
	}
	}; // AVLIterator

public:

	typedef AVLNode	Node;

	// https://www.cplusplus.com/reference/memory/allocator/rebind/
	typedef typename Allocator::template rebind<Node>::other	 allocator_type;
	typedef typename Allocator::pointer          	 pointer;
	typedef typename Allocator::const_pointer    	 const_pointer;
	typedef AVLIterator<Node> 		iterator;
	typedef AVLIterator<Node const> const_iterator;
	typedef ft::reverse_iterator<iterator>       	 reverse_iterator; // think of the ft:: part or the linter won't like
	typedef ft::reverse_iterator<const_iterator> 	 const_reverse_iterator;

	// CANONICAL FORM //////////////////////////////////////////////////////////
	//
	AVLTree(const Compare &comp = Compare(), const Allocator &alloc = Allocator()): _head(NULL), _comp(comp), _alloc(alloc) { }
	AVLTree(AVLTree const &copy): _head(copy.head), _comp(copy._comp), _alloc(copy.alloc) { }
	AVLTree	&operator=(AVLTree const &copy) { // shallow copy
		if (this == &copy)
			return (*this);
		_head = copy._head;
		_comp = copy._comp;
		_alloc = copy._alloc;
		return (*this);
	}
	virtual ~AVLTree(void) {
		_delete_subtree(_head);
	}

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

	size_t	height(void) const {
		return(height(_head));
	}
	static size_t	height(Node *node) {
		if (!node)
			return (0);
		return (1 + std::max(height(node->left), height(node->right)));
	}
	Node	*new_node(value_type const &data) {
		Node	*node = _alloc.allocate(1);
		_alloc.construct(node, data);
		return (node);
	}

	void	insert(value_type const &data) {
		if (!_head)
			_head = new_node(data);
		else {
			Node	*node = _head;
			Node	*parent = NULL;
			Node	**anode = NULL;
			while (node) {
				parent = node;
				if (_comp(data, node->data))
					anode = &node->left;
				else
					anode = &node->right;
				node = *anode;
			}
			*anode = new_node(data);
			(*anode)->parent = parent;
			if (parent->parent)
				_balance(parent->parent);
		}
	}

	Node	*min_node(void) {
		Node *node(_head);
		if (!node)
			return (NULL);
		while (node->left)
			node = node->left;
		return (node);
	}
	Node	*max_node(void) {
		Node *node(_head);
		if (!node)
			return (NULL);
		while (node->right)
			node = node->right;
		return (node);
	}
	iterator	begin() {
		return (iterator(min_node()));
	}
	const_iterator	begin() const {
		return (const_iterator(min_node()));
	}
	iterator	end() { // FIX: need to create a special node for the end
		return (NULL);
	}
	const_iterator	end() const {
		return (NULL);
	}

	private:

	// PRIVATE METHODS /////////////////////////////////////////////////////////
	//

	// Returns the address of the branch where the node is attached
	// can be &_head, &node->parent->left or &node->parent->right
	// It is used to perform rotations
	Node	**_node_branch_address(Node const *node) {
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
	Node	*_left_rotate(Node *old_parent) {
		Node	*new_parent = old_parent->right;
		Node	**root = _node_branch_address(old_parent);
		*root = new_parent;
		new_parent->parent = old_parent->parent;
		old_parent->parent = new_parent;
		old_parent->right = new_parent->left;
		if (old_parent->right)
			old_parent->right->parent = old_parent;
		new_parent->left = old_parent;
		return (*root);
	}
	// Left son takes place of the node
	Node	*_right_rotate(Node *old_parent) {
		Node	*new_parent = old_parent->left;
		Node	**root = _node_branch_address(old_parent);
		*root = new_parent;
		new_parent->parent = old_parent->parent;
		old_parent->parent = new_parent;
		old_parent->left = new_parent->right;
		if (old_parent->left)
			old_parent->left->parent = old_parent;
		new_parent->right = old_parent;
		return (*root);
	}
	void	_balance(Node *node) {
		// RIGHT IMBALANCE / LEFT ROTATION
		if (height(node->right) > height(node->left) + 1 && height(node->right->right) >= height(node->right->left))
			node = _left_rotate(node);
		// LEFT IMBALANCE / RIGHT ROTATION
		else if (height(node->left) > height(node->right) + 1 && height(node->left->left) >= height(node->left->right))
			node = _right_rotate(node);
		// RL IMBALANCE / RL ROTATION
		else if (height(node->right) > height(node->left) + 1 && height(node->right->right) < height(node->right->left)) {
			_right_rotate(node->right);
			node = _left_rotate(node);
		}
		// LR IMBALANCE / LR ROTATION
		else if (height(node->left) > height(node->right) + 1 && height(node->left->left) < height(node->left->right)) {
			_left_rotate(node->left);
			node = _right_rotate(node);
		}

		if (node->parent)
			_balance(node->parent);
	}
	void	_delete_node(Node *node) {
		_alloc.destroy(node);
		_alloc.deallocate(node, 1);
	}
	void	_delete_subtree(Node *node) {
		if (!node)
			return ;
		if (node->left)
			_delete_subtree(node->left);
		if (node->right)
			_delete_subtree(node->right);
		_delete_node(node);

	}
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
	value_compare	_comp;
	allocator_type	_alloc;
	Node	*_end;
};

}
#endif
