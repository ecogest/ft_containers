/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:14:19 by mjacq             #+#    #+#             */
/*   Updated: 2022/03/10 10:54:58 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef> // std::ptrdiff_t
# include <iterator>

namespace ft {

// ref: https://en.cppreference.com/w/cpp/iterator/iterator_traits

template< class Iter >
struct iterator_traits {
    typedef typename Iter::difference_type   difference_type;
    typedef typename Iter::value_type        value_type;
    typedef typename Iter::pointer           pointer;
    typedef typename Iter::reference         reference;
    typedef typename Iter::iterator_category iterator_category;
};

template< class T >
struct iterator_traits<T*> {
    typedef std::ptrdiff_t                  difference_type;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template< class T >
struct iterator_traits<const T*> {
    typedef std::ptrdiff_t                  difference_type;
    typedef T                               value_type;
    typedef const T*                        pointer;
    typedef const T&                        reference;
    typedef std::random_access_iterator_tag iterator_category;
};

// Iterator base class

template<class Category, class T, class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

// Iterator tags (utiliser ceux de std pour assurer la compatibilité)

struct input_iterator_tag  {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag         {};
struct bidirectional_iterator_tag : public forward_iterator_tag       {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// TODO: reverse_iterator (https://en.cppreference.com/w/cpp/iterator/reverse_iterator)
template <class Iterator>
class reverse_iterator
    : public iterator<typename iterator_traits<Iterator>::iterator_category,
                      typename iterator_traits<Iterator>::value_type,
                      typename iterator_traits<Iterator>::difference_type,
                      typename iterator_traits<Iterator>::pointer,
                      typename iterator_traits<Iterator>::reference>
{
protected:
    Iterator current;
public:
    typedef Iterator                                            iterator_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::reference       reference;
    typedef typename iterator_traits<Iterator>::pointer         pointer;

    reverse_iterator();
    explicit reverse_iterator(Iterator x);
    template <class U> reverse_iterator(const reverse_iterator<U>& u);
    template <class U> reverse_iterator& operator=(const reverse_iterator<U>& u);
    Iterator base() const;
    reference operator*() const;
    pointer   operator->() const;
    reverse_iterator& operator++();
    reverse_iterator  operator++(int);
    reverse_iterator& operator--();
    reverse_iterator  operator--(int);
    reverse_iterator  operator+ (difference_type n) const;
    reverse_iterator& operator+=(difference_type n);
    reverse_iterator  operator- (difference_type n) const;
    reverse_iterator& operator-=(difference_type n);
    reference         operator[](difference_type n) const;
};

template <class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template <class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y);

template< class Iterator >
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

template <class Iterator>
reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n,
          const reverse_iterator<Iterator>& x);

}

#endif
