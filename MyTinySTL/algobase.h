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
}

}

#endif // MY_TINY_STL_H_