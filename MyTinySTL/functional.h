#ifndef MY_TINY_STL_H_
#define MY_TINY_STL_H_

// 该头文件包含了 mystl 的函数对象于哈希函数

#include <cstddef>

namespace mystl {

// 定义一元函数的参数型别和返回值型别
template<typename Arg, typename Result>
struct unarg_function {
    using argument_type = Arg;
    using result_type   = Result;
};

// 定义二元函数的参数型别和返回值型别
template<typename Arg1, typename Arg2, typename Result>
struct binary_function {
    using first_argument_type  = Arg1;
    using second_argument_type = Arg2;
    using result_type          = Result;
};

// 函数对象：加法
template<typename T>
struct plus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x + y; }
};

// 函数对象：减法
template<typename T>
struct minus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x - y; }
};

// 函数对象：乘法
template<typename T>
struct multiplies : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x * y; }
};

// 函数对象：除法
template<typename T>
struct divides : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x / y; }
};

// 函数对象：取模
template<typename T>
struct modulus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x % y; }
};

// 函数对象：取负
template<typename T>
struct negate : public unarg_function<T, T> {
    T operator()(const T& x) { return -x; }
};

// 加法的证同元素
template<typename T>
T identity_element(plus<T>) { return T(0); }

// 乘法的正同元素
template<typename T>
T identity_element(multiplies<T>) { return T(1); }

// 函数对象：等于
template<typename T>
struct equal_to : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x == y; }
};

// 函数对象：不等于
template<typename T>
struct not_equal_to : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x != y; }
};

// 函数对象：大于
template<typename T>
struct greater : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x > y; }
};

// 函数对象：小于
template<typename T>
struct less : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x < y; }
};

// 函数对象：大于等于
template<typename T>
struct greater_equal : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x >= y; }
};

// 函数对象：小于等于
template<typename T>
struct less_equal : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x <= y; }
};

// 函数对象：逻辑与
template<typename T>
struct logical_and : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x && y; }
};

// 函数对象：逻辑或
template<typename T>
struct logical_or : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x || y; }
};

// 函数对象：逻辑非
template<typename T>
struct logical_not : public unarg_function<T, bool> {
    bool operator()(const T& x) { return !x; }
};

}

#endif // MY_TINY_STL_H_