#ifndef MY_TINY_TYPE_TRAITS_H_
#define MY_TINY_TYPE_TRAITS_H_

// 这个头文件用于提取类型信息

// use standard header for type_traits
#include <type_traits>

namespace mystl {
    //helper struct

    template<typename T, T v>
    struct m_integral_constant {
        static constexpr T value = v;
    };

    template<bool b>
    using m_bool_constant = m_integral_constant<bool, b>;

    using m_true_type = m_bool_constant<true>;
    using m_false_type = m_bool_constant<false>;

    /**********************************************************************/
    // type traits

    // is_pair

    // --- forward declaration begin
    template<typename T, typename U>
    struct pair;
    // --- forward declaration end

    template<typename T>
    struct is_pair : mystl::m_false_type {};

    template<typename T, typename U>
    struct is_pair<mystl::pair<T, U>> : mystl::m_true_type {};
    
}   // namespzce mystl

#endif  // MY_TINY_TYPE_TRAITS_H