#pragma once
#include "BaseSorter.hpp"

namespace sem3 {
    template <typename T>
    class QuickSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;
        //partition
        //random pivot
        int partition(int left, int right);
        int randomPivot(int left, int right);
        void quickSort(int left, int right);
    public:
        QuickSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {};
        void sort() override;
    };

    template <typename T>
    void QuickSorter<T>::sort() {
        quickSort(0, arr->getSize() - 1);
    }

    template <typename T>
    int QuickSorter<T>::randomPivot(int left, int right) {
        std::srand(time(NULL));
        return left + rand() % (right - left);
    }

    template <typename T>
    int QuickSorter<T>::partition(int left, int right) {
        int pivot = randomPivot(left, right);
        T pivotValue = arr->get(pivot);
        int i = left;
        int j = right;
        while (i <= j) {
            while (cmp(arr->get(i), pivotValue) < 0) {
                ++i;
            }
            while (cmp(arr->get(j), pivotValue) > 0) {
                --j;
            }
            if (i >= j) {
                break;
            }
            std::swap((*arr)[i], (*arr)[j]);
            ++i;
            --j;
        }
        return j;
    }

    template <typename T>
    void QuickSorter<T>::quickSort(int left, int right) {
        if (left < right) {
            int pivot = partition(left, right);
            quickSort(left, pivot);
            quickSort(pivot + 1, right);
        }
    }
} // namespace sem3