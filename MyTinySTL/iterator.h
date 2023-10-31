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
    struct random_iterator_tag : public bidirectional_iterator_tag {};

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
    
}

#endif  //  MY_TINY_ITERATOR_H_