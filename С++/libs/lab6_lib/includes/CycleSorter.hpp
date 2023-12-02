#pragma once
#include "BaseSorter.hpp"

namespace sem3 {
    template <typename T>
    class CycleSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

    public:
        CycleSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort() override;
    };

    template <typename T>
    void CycleSorter<T>::sort() {
        int n = arr->getSize();

        for (int cycleStart = 0; cycleStart < n - 1; ++cycleStart) {
            while (true) {
                int pos = cycleStart;
                T item = arr->get(cycleStart);
                for (int i = cycleStart + 1; i < n; ++i) {
                    if (cmp(arr->get(i), item) < 0) {
                        ++pos;
                    }
                }

                if (pos == cycleStart) {
                    break;
                }

                while (cmp(item, arr->get(pos)) == 0) {
                    ++pos;
                }
                std::swap((*arr)[pos], (*arr)[cycleStart]);
            }
        }
    }
} // namespace sem3