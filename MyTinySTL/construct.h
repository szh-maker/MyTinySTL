#ifndef MY_TINY_CONSTRUCT_H_
#define MY_TINY_CONSTRUCT_H_

// 该头文件包含两个函数 construct，destroy
// construct：负责对象的构建
// destroy：负责对象的析构

#include <new>

#include "type_traits.h"
#include "iterator.h"
#include "util.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4100) // unused parameter
#endif  // _MSVC_VER

namespace mystl {
    // construct 构造对象

    template<typename Ty>
    void construct(Ty* ptr) {
        ::new((void*)ptr) Ty();
    }

    template<typename Ty1, typename Ty2>
    void construct(Ty1* ptr, const Ty2& value) {
        ::new ((void*)ptr) Ty1(value);
    }

    template<typename Ty, typename... Args>
    void construct(Ty1* ptr, Args... args) {
        ::new ((void*)ptr) Ty(mystl::forward<Args>(args)...);
    }

    // destroy 将对象析构
    template<typename Ty>
    void destroy_one(Ty*, std::true_type) {}

    template<typename Ty>
    void destroy_one(Ty* pointer, std::false_type) {
        if(pointer != nullptr) {
            pointer->~Ty();
        }
    }

    template<typename ForwardIter>
    void destroy_cat(ForwardIter, ForwardIter, std::true_type) {}

    template<typename ForwardIter>
    void destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
        for(; first != last; ++first) {
            destroy(&*first);
        }
    }

    template<typename Ty>
    void destroy(Ty* pointer) {
        destroy_one(pointer, std::is_trivially_destructible<Ty>{});
    }

    template<typename ForwardIter>
    void destroy(ForwardIter first, ForwardIter last) {
        destroy_cat(first, last, std::is_trivially_destructible<
            typename iterator_traits<ForwardIter>::value_type>{});
    }

}

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#endif // MY_TINY_CONSTRUCT_H_