#pragma once
#include "BaseSorter.hpp"

namespace sem3 {
    template <typename T>
    class HeapSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

        void heapify(int n, int i);

    public:
        HeapSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}

        void sort() override;
    };

    template <typename T>
    void HeapSorter<T>::heapify(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && cmp(arr->get(left), arr->get(largest)) > 0) {
            largest = left;
        }
        if (right < n && cmp(arr->get(right), arr->get(largest)) > 0) {
            largest = right;
        }
        if (largest != i) {
            std::swap((*arr)[i], (*arr)[largest]);
            heapify(n, largest);
        }
    }

    template <typename T>
    void HeapSorter<T>::sort() {
        int n = arr->getSize();
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(n, i);
        }
        for (int i = n - 1; i >= 0; i--) {
            std::swap((*arr)[0], (*arr)[i]);
            heapify(i, 0);
        }
    }
}