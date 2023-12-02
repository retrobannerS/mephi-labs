#pragma once
#include "BaseSorter.hpp"

namespace sem3 {
    template <typename T>
    class GnomeSorter : public BaseSorter<T> {
    private:
    using BaseSorter<T>::arr;
    using BaseSorter<T>::cmp;
    public:
        GnomeSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort() override;
    };
    template <typename T>
    void GnomeSorter<T>::sort() {
        int i = 1;
        int j = 2;
        while (i < arr->getSize()) {
            if (cmp(arr->get(i - 1), arr->get(i)) <= 0) {
                i = j;
                j++;
            } else {
                std::swap((*arr)[i - 1], (*arr)[i]);
                i--;
                if (i == 0) {
                    i = j;
                    j++;
                }
            }
        }
    }
} // namespace sem3