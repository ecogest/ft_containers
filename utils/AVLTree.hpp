/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVLTree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:09:49 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/11 22:17:48 by mjacq            ###   ########.fr       */
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
template <class Data, class Compare = std::less<Data>, class Allocator = std::allocator<Data>, bool AreKeysUnique = true >
class AVLTree {

private:
	// AVL Node ////////////////////////////////////////////////////////////////
	//
	struct AVLNode {
		typedef Data	value_type;
		typedef AVLNode	Node;

		Data		data;
		Node		*left;
		Node		*right;
		Node		*parent;

		AVLNode(void)
			: data(), left(NULL), right(NULL), parent(NULL) { }
		AVLNode(const Data &data)
			: data(data), left(NULL), right(NULL), parent(NULL) { }
		AVLNode(Node const &copy)
			: data(copy.data), left(copy.left), right(copy.right), parent(copy.parent) { }
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


	// AVL ITERATOR ////////////////////////////////////////////////////////////
	//
	template <class NodeType, class ValueType>	// NOTE: we need to specify ValueType in order to apply constness if necessary
	class AVLIterator {

	public:
		typedef typename std::ptrdiff_t					difference_type;
		typedef ValueType								value_type;
		typedef value_type*								pointer;
		typedef value_type&								reference;
		typedef typename ft::bidirectional_iterator_tag	iterator_category;

	private:
		typedef NodeType										node_type;
		typedef NodeType&										node_reference;
		typedef NodeType*										node_pointer;
		typedef AVLIterator										iterator;
		typedef AVLIterator<const NodeType, const ValueType>	const_iterator;

		node_pointer	_node;

	public:
		AVLIterator(): _node(0)                              { }
		AVLIterator(node_pointer ptr): _node(ptr)            { }
		AVLIterator(AVLIterator const &it): _node(it.base()) { }
		~AVLIterator()                                       { }

		AVLIterator	&operator=(AVLIterator const &it) { _node = it._node; return (*this); }

		operator const_iterator() const { return (_node); }
		// Same as:
		// operator AVLIterator<const NodeType, const ValueType>() const {
		// 	return AVLIterator<const NodeType, const ValueType>(_node); }

		// (1) [LegacyBidirectionalIterator] < LegacyForwardIterator
		// (2) [LegacyForwardIterator] < LegacyIterator, LegacyInputOperator, DefaultConstructible
		// (3) [LegacyInputOperator] < (LegacyOperator), EquallyComparable
		// (4) [EquallyComparable]
		// (5) [LegacyIterator]
		iterator	&operator--()                               { _node = _prev(_node) ; return (*this); }                   // (1)
		iterator	operator--(int)                             { iterator tmp(_node); _node = _prev(_node); return (tmp); } // (1)
		iterator	operator++(int)                             { iterator tmp(_node); _node = _next(_node); return (tmp); } // (2)
		bool		operator!=(const_iterator const &rhs) const { return (_node != rhs.base()); }                            // (3)
		pointer		operator->() const                          { return (&_node->data); }                                   // (3)
		bool		operator==(const_iterator const &rhs) const { return (_node == rhs.base()); }                            // (4)
		reference	operator*(void) const                       { return _node->data; }                                      // (5)
		iterator	&operator++()                               { _node = _next(_node); return (*this); }                    // (5)

		node_pointer	base(void) const  { return _node; } // (getter)

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

	// TYPEDEFS ////////////////////////////////////////////////////////////////
	//
	typedef Data				value_type;
	typedef Compare				value_compare;
	typedef std::size_t			size_type; // check type
	typedef std::ptrdiff_t		difference_type; // check type
	typedef value_type&			reference;
	typedef const value_type&	const_reference;

	typedef Allocator											allocator_type;
	typedef typename Allocator::pointer		 					pointer;
	typedef typename Allocator::const_pointer		 			const_pointer;

	typedef AVLNode													node_type;
	typedef typename Allocator::template rebind<node_type>::other	node_allocator_type;
	// (https://www.cplusplus.com/reference/memory/allocator/rebind/)

	typedef AVLIterator<node_type, value_type> 				iterator;
	typedef AVLIterator<node_type const, value_type const>	const_iterator;
	typedef ft::reverse_iterator<iterator>		 			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> 			const_reverse_iterator;

	// CANONICAL FORM //////////////////////////////////////////////////////////
	//
	AVLTree(const Compare &comp = Compare(), const Allocator &alloc = Allocator())
		: _head(NULL), _comp(comp), _alloc(alloc), _node_alloc(alloc), _are_keys_unique(AreKeysUnique) {
			_init_end(); _head = _end;
		}
	AVLTree(AVLTree const &copy)
		: _comp(copy._comp), _alloc(copy._alloc), _node_alloc(copy._alloc), _are_keys_unique(AreKeysUnique) {
			_init_end(); _head = _end;
			for (const_iterator it = copy.begin(); it != copy.end(); it++)
				insert(*it);
		}
	AVLTree	&operator=(AVLTree const &copy) { // deep copy
		if (this == &copy)
			return (*this);
		clear();
		_comp = copy._comp;
		_alloc = copy._alloc;
		_node_alloc = copy._node_alloc;
		for (const_iterator it = copy.begin(); it != copy.end(); it++)
			insert(*it);
		return (*this);
	}
	virtual ~AVLTree(void) { _delete_subtree(_head); }

	// METHODS /////////////////////////////////////////////////////////////////
	//
	allocator_type		get_allocator() const      { return _alloc; }
	node_allocator_type	get_node_allocator() const { return _node_alloc; }
	void				clear()                    { _clear(_head); }
	size_type			size() const               { return (_size(_head)); }
	bool				empty() const              { return (_head == _end && !_end->left); }

	template <class Key, class KeyGetter, class Comp>
	iterator find( const Key& k, KeyGetter const &key, Comp const &comp ) const {
		node_type * node = _find_node(_head, k, key, comp);
		if (node)
			return (node);
		else
			return (_end);
	}

	ft::pair<iterator, bool>	insert(value_type const &data) {
		node_type	*node = _head;
		node_type	*parent = NULL;
		node_type	**anode = NULL;
		while (node) {
			parent = node;
			if (node == _end || _comp(data, node->data))
				anode = &node->left;
			else if (_comp(node->data, data) || !_are_keys_unique)
				anode = &node->right;
			else
				return ft::make_pair<iterator, bool>(node, false);
			node = *anode;
		}
		*anode = _new_node(data);
		iterator	it_ret(*anode);
		(*anode)->parent = parent;
		if (parent->parent)
			_balance(parent->parent);
		return (ft::make_pair<iterator, bool>(it_ret, true));
	}

	void	erase(iterator it) {
		node_type	*node = it.base();
		if (node == _end)
			return ;
		if (node) {
			node_type	*parent = node->parent;
			node_type	**parent_anchor = NULL;
			if (parent) {
				if (node == node->parent->left)
					parent_anchor = &node->parent->left;
				if (node == node->parent->right)
					parent_anchor = &node->parent->right;
			}
			else
				parent_anchor = &_head;
			// leaf case
			if (!node->left && !node->right)
				*parent_anchor = NULL;
			// single child
			else if (node->left && !node->right) {
				*parent_anchor = node->left;
				(*parent_anchor)->parent = parent;
			}
			else if (node->right && !node->left) {
				*parent_anchor = node->right;
				(*parent_anchor)->parent = parent;
			}
			else { // 2 children
				++it;
				node_type	*next_node = it.base();
				*parent_anchor = next_node;
				if (next_node == next_node->parent->left)
					next_node->parent->left = next_node->left;
				else if (next_node == next_node->parent->right)
					next_node->parent->right = next_node->right; // (1)
				next_node->left = node->left;
				node->left->parent = next_node;
				next_node->right = node->right;
				if (node->right) // (1) -> can NULL node->right if next_node == node->right
					node->right->parent = next_node;
				next_node->parent = node->parent;
			}
			if (*parent_anchor)
				_balance(*parent_anchor);
			else if (parent)
				_balance(parent);
			else
				_balance(_head);
			_delete_node(node);
		}
	}

	void swap( AVLTree& other ) { (void)other; }

	// ITERATORS ///////////////////////////////////////////////////////////////
	//
	iterator				begin()        { return (iterator(_min_node())); }
	const_iterator			begin() const  { return (const_iterator(_min_node())); }
	iterator				end()          { return (_end); }
	const_iterator			end() const    { return (_end); }
	reverse_iterator		rbegin()       { return (reverse_iterator(end())); }
	const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
	reverse_iterator		rend()         { return (reverse_iterator(begin())); }
	const_reverse_iterator	rend() const   { return (const_reverse_iterator(begin())); }

	// PRINT ///////////////////////////////////////////////////////////////////
	//
	void		print_infix(void) const {
		if (_head != _end || _end->left)
			_print_infix(_head);
		std::cout << std::endl;
	}
	void	print_2d(void) const {
		ft::vector<std::string> output_vector;
		_print_2d(_head, output_vector, 0);
		std::cout << std::endl;
		for (size_t i = 0; i < output_vector.size(); i++)
			std::cout << output_vector[i] << std::endl;
	}

	// PRIVATE METHODS /////////////////////////////////////////////////////////
	//
	private:

	void	_init_end(void) {
		_end = _node_alloc.allocate(1);
		_end->left = NULL;
		_end->right = NULL;
		_end->parent = NULL;
	}
	void	_set_end_parentage(node_type *parent) {
		_end->parent = parent;
		parent->right = _end;
	}
	// Returns the address of the branch where the node is attached
	// can be &_head, &node->parent->left or &node->parent->right
	// It is used to perform rotations
	node_type	**_node_branch_address(node_type const *node) {
		node_type	**root;
		if (node == _head)
			root = &_head;
		else if (node == node->parent->left)
			root = &node->parent->left;
		else
			root = &node->parent->right;
		return (root);
	}
	size_type	_size(node_type *node) const {
		if (!node)
			return (0);
		else if (node == _end)
			return (_size(node->left));
		else
			return (1 + _size(node->left) + _size(node->right));
	}
	// size_type	_height(void) const { return(_height(_head)); }
	size_type	_height(node_type *node) const {
		return (node ? 1 + std::max(_height(node->left), _height(node->right)): 0);
	}
	// Remove everything except the end
	void _clear(node_type *node) {
		if (!node)
			return ;
		if (node->left)
			_clear(node->left);
		if (node->right)
			_clear(node->right);
		if (node == _end) {
			node->left = NULL; node->right = NULL; node->parent = NULL;
			_head = _end;
		}
		else
			_delete_node(node);
	}
	// Right son takes place of the node
	node_type	*_left_rotate(node_type *old_parent) {
		node_type	*new_parent = old_parent->right;
		node_type	**root = _node_branch_address(old_parent);
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
	node_type	*_right_rotate(node_type *old_parent) {
		node_type	*new_parent = old_parent->left;
		node_type	**root = _node_branch_address(old_parent);
		*root = new_parent;
		new_parent->parent = old_parent->parent;
		old_parent->parent = new_parent;
		old_parent->left = new_parent->right;
		if (old_parent->left)
			old_parent->left->parent = old_parent;
		new_parent->right = old_parent;
		return (*root);
	}
	void	_balance(node_type *node) {
		// RIGHT IMBALANCE / LEFT ROTATION
		if (_height(node->right) > _height(node->left) + 1 && _height(node->right->right) >= _height(node->right->left))
			node = _left_rotate(node);
		// LEFT IMBALANCE / RIGHT ROTATION
		else if (_height(node->left) > _height(node->right) + 1 && _height(node->left->left) >= _height(node->left->right))
			node = _right_rotate(node);
		// RL IMBALANCE / RL ROTATION
		else if (_height(node->right) > _height(node->left) + 1 && _height(node->right->right) < _height(node->right->left)) {
			_right_rotate(node->right);
			node = _left_rotate(node);
		}
		// LR IMBALANCE / LR ROTATION
		else if (_height(node->left) > _height(node->right) + 1 && _height(node->left->left) < _height(node->left->right)) {
			_left_rotate(node->left);
			node = _right_rotate(node);
		}

		if (node->parent)
			_balance(node->parent);
	}
	node_type	*_new_node(value_type const &data) {
		node_type	*node = _node_alloc.allocate(1);
		_node_alloc.construct(node, data);
		return (node);
	}
	void	_delete_node(node_type *node) {
		if (node != _end)
			_node_alloc.destroy(node);
		_node_alloc.deallocate(node, 1);
	}
	void	_delete_subtree(node_type *node) {
		if (!node)
			return ;
		if (node->left)
			_delete_subtree(node->left);
		if (node->right)
			_delete_subtree(node->right);
		_delete_node(node);
	}
	node_type	*_min_node(void) const {
		node_type *node(_head);
		while (node->left)
			node = node->left;
		return (node);
	}
	template <class Key, class KeyGetter, class Comp>
	node_type	*_find_node(node_type *begin, const Key &k, KeyGetter const &key, Comp const &comp) const {
		if (!begin)
			return (NULL);
		if (begin == _end)
			return (_find_node(begin->left, k, key, comp));
		else if (comp(k, key(begin->data)))
			return (_find_node(begin->left, k, key, comp));
		else if (comp(key(begin->data), k))
			return (_find_node(begin->right, k, key, comp));
		else
			return (begin);
	}
	void	_print_infix(node_type *node) const {
		if (!node)
			return ;
		_print_infix(node->left);
		if (node != _end)
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
	void	_print_2d(node_type *node, ft::vector<std::string> &v, size_t level) const {
		if (!node)
			return ;
		// if (node == _end)
		// {
		// 	_print_2d(node->left, v, level);
		// 	return ;
		// }
		std::string	left_padding(" ");
		std::ostringstream	oss;
		if (node != _end)
			oss << '|' << node->data << '|';
		else
			oss << '|' << "✋" << '|';
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
	node_type			*_head;
	node_type			*_end;
	value_compare		_comp;
	allocator_type		_alloc; // we could probably drop this attribute and rebind _node_alloc in get_allocator()
	node_allocator_type	_node_alloc;
	bool const			_are_keys_unique;
};

}
#endif
