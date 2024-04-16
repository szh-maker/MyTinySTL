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
    bool operator()(const T& x) const { return !x; }
};

// 证同函数：不会改变元素，返回本身
template<typename T>
struct identity : public unarg_function<T, bool> {
    const T& operator()(const T& x) const { return x; }
};

// 选择函数：接受一个 pair， 返回第一个元素
template<typename Pair>
struct selectfirst : public unarg_function<Pair, typename Pair::first_type> {
    const typename Pair::first_type& operator()(const Pair& x) const {
        return x.first;
    }
};

// 选择函数：接受一个 pair，返回第二个元素
template<typename Pair>
struct selectsecond : public unarg_function<Pair, typename Pair::second_type> {
    const typename Pair::second_type& operator()(const Pair& x) const {
        return x.second;
    }
};

// 投射函数：返回第一参数
template<typename Arg1, typename Arg2>
struct projectfirst : public binary_function<Arg1, Arg2, Arg1> {
    Arg1 operator()(const Arg1& x, const Arg2&) const { return x; }
};

// 投射函数：返回第二参数
template<typename Arg1, typename Arg2>
struct projectsecond : public binary_function<Arg1, Arg2, Arg2> {
    Arg2 operator()(const Arg1&, const Arg2& y) const { return y; }
};

/*********************************************************************/
// 哈希函数对象

// 对于大部分类型，hash function 什么都不做
template<typename Key>
struct hash {};

// 针对指针的偏特化版本
template<typename T>
struct hash<T*> {
    size_t operator()(T* p) const noexcept {
        return reinterpret_cast<size_t>(p);
    }
};

// 对于整数类型，只是返回原值
#define MYSTL_TRIVAL_HASH_FCN(Type)                \
template<> struct hash<Type> {                     \
    size_t operator()(Type val) const noexcept     \
    { return static_cast<size_t>(val); }           \
};

MYSTL_TRIVAL_HASH_FCN(bool)

MYSTL_TRIVAL_HASH_FCN(char)

MYSTL_TRIVAL_HASH_FCN(signed char)

MYSTL_TRIVAL_HASH_FCN(unsigned char)

MYSTL_TRIVAL_HASH_FCN(wchar_t)

MYSTL_TRIVAL_HASH_FCN(char16_t)

MYSTL_TRIVAL_HASH_FCN(char32_t)

MYSTL_TRIVAL_HASH_FCN(short)

MYSTL_TRIVAL_HASH_FCN(unsigned short)

MYSTL_TRIVAL_HASH_FCN(int)

MYSTL_TRIVAL_HASH_FCN(unsigned int)

MYSTL_TRIVAL_HASH_FCN(long)

MYSTL_TRIVAL_HASH_FCN(unsigned long)

MYSTL_TRIVAL_HASH_FCN(long long)

MYSTL_TRIVAL_HASH_FCN(unsigned long long)

#undef MYSTL_TRIVAL_HASH_FCN

// 对于浮点数，逐位哈希
inline size_t bitwies_hash(const unsigned char* first, size_t count) {
#if (_MSC_VER && WIN64) || ((__GUNC__ || __clang__) && __SIZEOF_POINTER__ == 8)
    const size_t fnv_offset = 14695981039346656037ull;
    const size_t fnv_prime = 1099511628211ull;
#else

#endif
}

}

#endif // MY_TINY_STL_H_