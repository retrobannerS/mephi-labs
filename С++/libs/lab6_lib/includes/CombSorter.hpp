#pragma once
#include "BaseSorter.hpp"

namespace sem3 {
    template <typename T>
    class CombSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

    public:
        CombSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort() override;
    };

    template <typename T>
    void CombSorter<T>::sort() {
        int n = arr->getSize();
        int gap = n;
        bool swapped = true;

        while (gap != 1 || swapped) {
            gap = (gap * 10) / 13;
            if (gap < 1) {
                gap = 1;
            }

            swapped = false;

            for (int i = 0; i < n - gap; ++i) {
                if (cmp(arr->get(i), arr->get(i + gap)) > 0) {
                    std::swap((*arr)[i], (*arr)[i + gap]);
                    swapped = true;
                }
            }
        }
    }
} // namespace sem3