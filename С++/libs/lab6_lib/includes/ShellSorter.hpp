#pragma once
#include "BaseSorter.hpp"

namespace sem3 {
    template <typename T>
    class ShellSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;
        int getGap(int size);

    public:
        ShellSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp){};
        void sort() override;
    };

    template <typename T>
    void ShellSorter<T>::sort() {
        int size = arr->getSize();
        int gap = getGap(size);
        bool flag = true;
        while(gap != 0) {
            for (int i = gap; i < size; i += 1) {
                for (int j = i; j >= gap && cmp(arr->get(j - gap), arr->get(j)) > 0; j -= gap)
                    std::swap((*arr)[j], (*arr)[j - gap]);
            }
            gap = getGap(gap);
        }
    }

    template <typename T>
    int ShellSorter<T>::getGap(int size) {
        if (size <= 1) {
            return 0;
        }
        int gap = 1;
        while (gap < size / 3) {
            gap = 3 * gap + 1;
        }
        return gap;
    }
} // namespace sem3