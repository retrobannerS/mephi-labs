#pragma once
#include "BaseSorter.hpp"

namespace sem3 {
    template <typename T>
    class CocktailSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

    public:
        CocktailSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort() override;
    };

    template <typename T>
    void CocktailSorter<T>::sort() {
        int left = 0;
        int right = arr->getSize() - 1;
        while (left < right) {
            for (int i = left; i < right; ++i) {
                if (cmp(arr->get(i), arr->get(i + 1)) > 0) {
                    std::swap((*arr)[i], (*arr)[i + 1]);
                }
            }
            --right;
            for (int i = right; i > left; --i) {
                if (cmp(arr->get(i), arr->get(i - 1)) < 0) {
                    std::swap((*arr)[i], (*arr)[i - 1]);
                }
            }
            ++left;
        }
    }
} // namespace sem3