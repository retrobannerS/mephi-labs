#pragma once
#include "BaseSorter.hpp"
#include "SmartArraySequence.hpp"
#include <vector>

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
        if (arr->empty()) {
            return;
        }
        T min = arr->get(0);
        T max = arr->get(0);
        for (int i = 1; i < arr->getSize(); ++i) {
            if (cmp(arr->get(i), min) < 0) {
                min = arr->get(i);
            }
            if (cmp(arr->get(i), max) > 0) {
                max = arr->get(i);
            }
        }
        int range = max - min + 1;
        SmartArraySequence<int> count(range, 0);
        for (int i = 0; i < arr->getSize(); ++i) {
            count[arr->get(i) - min]++;
        }

        for (int i = 1; i < range; ++i) {
            count[i] += count[i - 1];
        }

        SmartArraySequence<T> output(arr->getSize());
        for (int i = arr->getSize() - 1; i >= 0; --i) {
            output[count[arr->get(i) - min] - 1] = arr->get(i);
            count[arr->get(i) - min]--;
        }
        for (int i = 0; i < arr->getSize(); ++i) {
            arr->set(i, output[i]);
        }
    }

} // namespace sem3