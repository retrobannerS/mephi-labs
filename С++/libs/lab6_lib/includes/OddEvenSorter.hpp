#pragma once
#include "BaseSorter.hpp"

namespace sem3 {
    template <typename T>
    class OddEvenSorter : public BaseSorter<T> {
    private:
    using BaseSorter<T>::arr;
    using BaseSorter<T>::cmp;
    public:
        OddEvenSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort() override;
    };
    template <typename T>
    void OddEvenSorter<T>::sort() {
        bool sorted = false;
        while (!sorted) {
            sorted = true;
            for (int i = 1; i < arr->getSize() - 1; i += 2) {
                if (cmp(arr->get(i), arr->get(i + 1)) > 0) {
                    std::swap((*arr)[i], (*arr)[i + 1]);
                    sorted = false;
                }
            }
            for (int i = 0; i < arr->getSize() - 1; i += 2) {
                if (cmp(arr->get(i), arr->get(i + 1)) > 0) {
                    std::swap((*arr)[i], (*arr)[i + 1]);
                    sorted = false;
                }
            }
        }
    }
} // namespace sem3