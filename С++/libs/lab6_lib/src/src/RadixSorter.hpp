#pragma once
#include "BaseSorter.hpp"
#include "SmartArraySequence.hpp"

namespace sem3 {
    template <typename T>
    class RadixSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

    public:
        RadixSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort() override;
    };
    template <typename T>
    void RadixSorter<T>::sort() {
        if (arr->empty()) {
            return;
        }

        int max = arr->get(0);
        for (int i = 1; i < arr->getSize(); ++i) {
            if (cmp(max, arr->get(i)) < 0) {
                max = arr->get(i);
            }
        }
        
        int exp = 1;
        while (max / exp > 0) {
            int bucket[10] = {0};
            for (int i = 0; i < arr->getSize(); ++i) {
                bucket[(arr->get(i) / exp) % 10]++;
            }
            for (int i = 1; i < 10; ++i) {
                bucket[i] += bucket[i - 1];
            }
            SharedPtr<SmartSequence<T>> output = SharedPtr<SmartSequence<T>>(new SmartArraySequence<T>(arr->getSize()));
            for (int i = arr->getSize() - 1; i >= 0; --i) {
                output->set(bucket[(arr->get(i) / exp) % 10] - 1, arr->get(i));
                bucket[(arr->get(i) / exp) % 10]--;
            }
            for (int i = 0; i < arr->getSize(); ++i) {
                arr->set(i, output->get(i));
            }
            exp *= 10;
        }
    }
} // namespace sem3