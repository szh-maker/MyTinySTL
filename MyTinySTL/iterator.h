#ifndef MY_TINY_ITERATOR_H_
#define MY_TINY_ITERATOR_H_

// 该头文件用于迭代器设计，包含了一些模板结构体与全局函数

#include <cstddef>
#include "type_traits.h"

namespace mystl {

    // 五种迭代器类型
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    // iterator 模板
    template<typename Category, typename T, typename Distance = ptrdiff_t,
        typename Pointer = T*, typename Reference = T&>
    struct iterator {
        typedef Category  iterator_category;
        typedef T         value_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Distance  distance_type;
    };

    // iterator traits

    template<typename T>
    struct has_iterator_cat {
    private:
        struct two { char a; char b;};
        template<typename U> static two test(...);
        template<typename U> static char test(typename U::iterator_category* = 0);
    public:
        static const bool value = sizeof(test<T>(0) == sizeof(char));
    };

    template<typename Iterator, bool>
    struct iterator_traits_impl {};

    template<typename Iterator>
    struct iterator_traits_impl<Iterator, true> {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::distance_type     distance_type;
    };
    
    template<typename Iterator, bool>
    struct iterator_traits_helper {};

    template<typename Iterator>
    struct iterator_traits_helper<Iterator, true> 
        : public iterator_traits_impl<Iterator, 
        std::is_constructible<typename Iterator::iterator_category, input_iterator_tag>::value ||
        std::is_constructible<typename Iterator::iterator_category, output_iterator_tag>::value> 
    {};

    // 萃取器的特性
    template<typename Iterator>
    struct iterator_traits 
        : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};
    
    // 针对原生指针的偏特化版本
    template<typename T>
    struct iterator_traits<T*> {
        typedef random_access_iterator_tag iterator_category;
        typedef T                          value_type;
        typedef T*                         pointer;
        typedef T&                         reference;
        typedef ptrdiff_t                  difference_type;
    };

    template<typename T>
    struct iterator_traits<const T*> {
        typedef random_access_iterator_tag iterator_category;
        typedef T                          value_type;
        typedef const T*                   pointer;
        typedef const T&                   reference;
        typedef ptrdiff_t                  difference_type;
    };

    template<typename T, typename U, bool = has_iterator_cat<iterator_traits<T>>::value>
    struct has_iterator_cat_of
        : public m_bool_constant<std::is_convertible<
            typename iterator_traits<T>::iterator_category, U>::value>
    {};

    // 萃取某种迭代器
    template<typename T, typename U>
    struct has_iterator_cat_of<T, U, false> : public m_false_type {};

    template<typename Iter>
    struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag> {};

    template<typename Iter>
    struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag> {};

    template<typename Iter>
    struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag> {};

    template<typename Iter>
    struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};

    template<typename Iter>
    struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag> {};

    template<typename Iterator>
    struct is_iterator :
        public m_bool_constant<is_input_iterator<Iterator>::value ||
            is_output_iterator<Iterator>::value> {};

    // 萃取某个迭代器的 category
    template<typename Iterator>
    typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator&) {
        typedef typename iterator_traits<Iterator>::iterator_category Category;
        return Category();
    }

    // 萃取某个迭代器的 distance_type
    template<typename Iterator>
    typename iterator_traits<Iterator>::difference_type*
    distance_type(const Iterator&) {
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
    }

    // 萃取某个迭代器的 value_type
    template<typename Iterator>
    typename iterator_traits<Iterator>::value_type*
    value_type(const Iterator&) {
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }

    // 以下函数用于计算迭代器间的距离

    // distance 的 input_iterator_tag 的版本
    template<typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag) {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while(first != last) {
            ++first;
            ++n;
        }
        return n;
    }

    // distance 的 random_access_iterator_tag 的版本
    template<typename RandomIter>
    typename iterator_traits<RandomIter>::difference_type
    distance_dispatch(RandomIter first, RandomIter last, random_access_iterator_tag) {
        return last - first;
    }

    template<typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last) {
        return distance_dispatch(first, last, iterator_category(first));
    }

    // 以下函数用于迭代器前进 n 个距离

    // advance 的 bidirectional_iterator_tag 的版本
    template<typename BidirectionalIterator, typename Distance>
    void advance_dispatch(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag) {
        if(n >= 0) {
            while(n--) ++i;
        } else {
            while(n++) --i;
        }
    }

    // advance 的 random_access_tag 的版本
    template<typename RandomIter, typename Distance>
    void advance_dispatch(RandomIter& i, Distance n, random_access_iterator_tag) {
        i += n;
    }

    template<typename InputIterator, typename Distance>
    void advance(InputIterator& i, Distance n) {
        advance_dispatch(i, n, iterator_category(i));
    }

    /**************************************************************************************/
    // 类模板：reverse_iterator
    // 反向迭代器，使前进为后退，后退为前进
    

}

#endif  //  MY_TINY_ITERATOR_H_