#pragma once
#include "BaseSorter.hpp"

namespace sem3 {
    template <typename T>
    class BinaryInsertionSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

    public:
        BinaryInsertionSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort() override;
    };

    template <typename T>
    void BinaryInsertionSorter<T>::sort() {
        for (int i = 1; i < arr->getSize(); ++i) {
            int left = 0;
            int right = i - 1;
            int mid = 0;
            while (left <= right) {
                mid = (left + right) / 2;
                if (cmp(arr->get(i), arr->get(mid)) < 0) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            arr->insertAt(left, arr->get(i));
            arr->removeAt(i + 1);
        }
    }
}