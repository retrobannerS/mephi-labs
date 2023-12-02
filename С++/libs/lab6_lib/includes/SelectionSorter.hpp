#pragma once
#include "BaseSorter.hpp"

namespace sem3 {
    template <typename T>
    class SelectionSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

    public:
        SelectionSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort() override;
    };

    template <typename T>
    void SelectionSorter<T>::sort() {
        for (int i = 0; i < arr->getSize() - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < arr->getSize(); ++j) {
                if (cmp(arr->get(j), arr->get(minIndex)) < 0) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                std::swap((*arr)[i], (*arr)[minIndex]);
            }
        }
    }
} // namespace sem3