#pragma once
#include "BaseSorter.hpp"
#include "SmartArraySequence.hpp"

namespace sem3 {
    template <typename T>
    class CountingSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

    public:
        CountingSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort() override;
    };

    template <typename T>
    void CountingSorter<T>::sort() {
        if(arr->empty()) {
            return;
        }
        int min = arr->get(0);
        int max = arr->get(0);
        for (int i = 1; i < arr->getSize(); ++i) {
            if (cmp(arr->get(i), min) < 0) {
                min = arr->get(i);
            }
            if (cmp(arr->get(i), max) > 0) {
                max = arr->get(i);
            }
        }
        int range = max - min + 1;
        auto count = make_unique<SmartArraySequence<int>>(range);
        for (int i = 0; i < arr->getSize(); ++i) {
            ++(*count)[arr->get(i) - min];
        }

        int index = 0;
        for (int i = min; i <= max; ++i) {
            while ((*count)[i - min] > 0) {
                (*arr)[index++] = i;
                (*count)[i - min]--;
            }
        }
    }
} // namespace sem3