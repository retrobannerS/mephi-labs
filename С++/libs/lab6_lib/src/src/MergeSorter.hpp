#pragma once
#include "BaseSorter.hpp"
#include "SmartListSequence.hpp"

namespace sem3 {
    template <typename T>
    class MergeSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

        void merge(SharedPtr<SmartSequence<T>> left, SharedPtr<SmartSequence<T>> right);

    public:
        MergeSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}

        void sort() override;
    };

    template <typename T>
    void MergeSorter<T>::merge(SharedPtr<SmartSequence<T>> left, SharedPtr<SmartSequence<T>> right) {
        int i = 0, j = 0;
        while (i < left->getSize() && j < right->getSize()) {
            if (cmp(left->get(i), right->get(j)) < 0) {
                arr->set(i + j, left->get(i));
                i++;
            } else {
                arr->set(i + j, right->get(j));
                j++;
            }
        }
        while (i < left->getSize()) {
            arr->set(i + j, left->get(i));
            i++;
        }
        while (j < right->getSize()) {
            arr->set(i + j, right->get(j));
            j++;
        }
    }

    template <typename T>
    void MergeSorter<T>::sort() {
        if (arr->getSize() <= 1) {
            return;
        }
        int middle = arr->getSize() / 2;
        SharedPtr<SmartSequence<T>> left(new SmartListSequence<T>());
        SharedPtr<SmartSequence<T>> right(new SmartListSequence<T>());
        for (int i = 0; i < middle; i++) {
            left->append(arr->get(i));
        }
        for (int i = middle; i < arr->getSize(); i++) {
            right->append(arr->get(i));
        }
        MergeSorter<T> leftSorter(left, cmp);
        MergeSorter<T> rightSorter(right, cmp);
        leftSorter.sort();
        rightSorter.sort();
        merge(left, right);
    }

} // namespace sem3