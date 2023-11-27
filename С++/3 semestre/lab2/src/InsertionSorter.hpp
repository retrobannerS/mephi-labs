#pragma once
#include "BaseSorter.hpp"
#include <utility>

namespace sem3 {
    template <typename T>
    class InsertionSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

    public:
        InsertionSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort() override;
    };

    template <typename T>
    void InsertionSorter<T>::sort() {
        int i, j;
        int n = arr->getSize();
        for (i = 1; i < n; i++) {
            j = i;
            while (j > 0 && cmp(arr->get(j - 1), arr->get(j)) > 0) {
                std::swap((*arr)[j], (*arr)[j - 1]);
                j--;
            }
        }
    }

} // namespace sem3