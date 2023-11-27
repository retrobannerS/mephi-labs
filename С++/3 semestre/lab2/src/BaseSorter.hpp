#pragma once
#include "SharedPtr.hpp"
#include "SmartSequence.hpp"

namespace sem3 {
    template <typename T>
    class BaseSorter {
    protected:
        SharedPtr<SmartSequence<T>> arr;
        int (*cmp)(T, T);
    public:
        BaseSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : arr(arr), cmp(cmp) {}
        virtual void sort() = 0;
        virtual ~BaseSorter() = default;
    };


} // namespace sem3
