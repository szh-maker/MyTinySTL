#ifndef MY_TINY_STL_H_
#define MY_TINY_STL_H_

// 该文件包含了 mystl 的基本算法

#include <cstring>

#include "iterator.h"
#include "util.h"

namespace mystl {

#ifdef max
#pragma message("#undefing macro max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing macro min")
#undef min
#endif // min

/*************************************************************************/
// max
// 取二者中的较大值，语义相等时保证返回第一个参数
/*************************************************************************/
template<typename T>
const T& max(const T& lhs, const T& rhs) {
    return lhs < rhs ? rhs : lhs;
};

// 重载版本使用函数对象 comp 代替比较操作
template<typename T, typename Compare>
const T& max(const T& lhs, const T& rhs, Compare compare) {
    return compare(lhs, rhs) ? rhs : lhs;
};

/************************************************************************/
// min
// 取二者中的较小值，语义相等时保证返回第一个参数
/************************************************************************/
template<typename T>
const T& min(const T& lhs, const T& rhs) {
    return rhs < lsh ? rhs : lhs;
};

// 重载版本使用函数对象 comp 代替比较操作
template<typename T, typename Compare>
const T& min(const T& lhs, const T& rhs, Compare compare) {
    return compare(rhs, lhs) ? rhs : lhs;
};

/************************************************************************/
// iter_swap
// 将两个迭代器所指对象对调
/************************************************************************/
template<typename FIter1, typename FIter2>
void iter_swap(FIter1 lhs, FIter2 rhs) {
    mystl::swap(*lhs, *rhs);
};

/************************************************************************/
// copy
// 把 [first, last)区间内的元素拷贝到 [result, result + (last - first))内
/************************************************************************/
// input_iterator_tag 版本
template<typename InputIter, typename OutputIter>
OutputIter unchecked_copy_cat(InputIter first, InputIter last, OutputIter result, mystl::input_iterator_tag) {
    for(; first != last; ++first, ++result) {
        *result = *first;
    }
    return result;
};

// random_access_iterator_tag 版本
template<typename RandomIter, typename OutputIter>
OutputIter unchecked_copy_cat(RandomIter first, RandomIter last, OutputIter result, mystl::random_access_iterator_tag) {
    for(auto n = last - first; n > 0; --n, ++first, ++result) {
        *result = *first;
    }
    return result;
};

template<typename InputIter, typename OutputIter>
OutputIter unchecked_copy(InputIter first, InputIter last, OutputIter result) {
    return unchecked_copy_cat(first, last, result, iterator_category(first));
};

// 为 trivially_copy_assignable 类型提供特化版本
template<typename Tp, typename Up>
typename std::enable_if<
    std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
    std::is_trivially_copy_assignable<Up>::value,
    Up*>::type
unchecked_copy(Tp* first, Tp* last, Up* result) {
    const auto n = static_cast<size_t>(last - first);
    if(n != 0)
        std::memmove(result, first, n * sizeof(Up));
    return result + n;
};

template<typename InputIter, typename OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter result) {
    return unchecked_copy(first, last, result);
};

/*********************************************************************/
// copy_backward
// 将[first, last)区间内的元素拷贝到[result - (last - first), result)内
/*********************************************************************/
// unchecked_copy_backward_cat 的 bidirectional_iterator_tag 版本
template<typename BidirectionalIter1, typename BidirectionalIter2>
BidirectionalIter2 unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
    BidirectionalIter2 result, mystl::bidirectional_iterator_tag) {
    while(first != last) {
        *--result = *--last;
    }
    return result;
}

// unchecked_copy_backward_cat 的 random_access_iterator_tag 版本
template<typename RandomIter1, typename BidirectionalIter2>
BidirectionalIter2 unchecked_copy_backward_cat(RandomIter1 first, RandomIter1 last,
    BidirectionalIter2 result, mystl::random_access_iterator_tag) {
    for(auto n = last - first; n > 0; --n) {
        *--result == *--last;
    }
    return result;
}

template<typename BidirectionalIter1, typename BidirectionalIter2>
BidirectionalIter2 unchecked_copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
    BidirectionalIter2 result) {
    return unchecked_copy_backward_cat(first, last, result, iterator_category(first));
}

// 为 trivially_copy_assignable 类型提供特化版本
template<typename Tp, typename Up>
typename std::enable_if<
    std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
    std::is_trivially_copy_assignable<Up>::value,
    Up*>::type
unchecked_copy_backward(Tp* first, Tp* last, Up* result) {
    const auto n = static_cast<size_t>(last - first);
    if(n != 0) {
        result -= n;
        std::memmove(result, first, n * sizeof(Up));
    }
    return result;
}

template<typename BidirectionalIter1, typename BidirectionalIter2>
BidirectionalIter2 copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, 
    BidirectionalIter2 result) {
    return unchecked_copy_backward(first, last, result);
}

}

#endif // MY_TINY_STL_H_