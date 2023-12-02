#pragma once
#include "BaseSorter.hpp"

namespace sem3 {
    template <typename T>
    class DoubleSelectionSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

    public:
        DoubleSelectionSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort() override;
    };

    template <typename T>
    void DoubleSelectionSorter<T>::sort() {
        int n = arr->getSize();
        for (int i = 0; i < n / 2; i++) {
            int min = i, max = i;
            for (int j = i + 1; j < n - i; j++) {
                if (cmp(arr->get(j), arr->get(min)) < 0) {
                    min = j;
                }
                if (cmp(arr->get(j), arr->get(max)) > 0) {
                    max = j;
                }
            }
            if (min == n - i - 1) {
                min = max;
            }
            std::swap((*arr)[max], (*arr)[n - i - 1]);
            std::swap((*arr)[min], (*arr)[i]);
        }
    }
} // namespace sem3