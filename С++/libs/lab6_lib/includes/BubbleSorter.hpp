#pragma once
#include "BaseSorter.hpp"
#include <utility>

namespace sem3 {
    template <typename T>
    class BubbleSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

    public:
        BubbleSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort() override;
    };

    template <typename T>
    void BubbleSorter<T>::sort() {
        int i, j;
        int n = arr->getSize();
        bool swapped;
        for (i = 0; i < n; i++) {
            swapped = false;
            for (j = 0; j < n - i - 1; j++) {
                if (cmp(arr->get(j), arr->get(j + 1)) > 0) {
                    std::swap((*arr)[j], (*arr)[j + 1]);
                    swapped = true;
                }
            }

            if (swapped == false)
                break;
        }
    }
} // namespace sem3