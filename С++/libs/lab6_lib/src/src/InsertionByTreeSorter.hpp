#pragma once
#include "BaseSorter.hpp"
#include "SmartListSequence.hpp"
#include "SmartSequence.hpp"
#include <UniquePtr.hpp>

namespace sem3 {
    template <typename T>
    class BinarySearchTree {
    private:
        UniquePtr<T> value;
        UniquePtr<BinarySearchTree<T>> left;
        UniquePtr<BinarySearchTree<T>> right;

    public:
        BinarySearchTree() : value(nullptr), left(nullptr), right(nullptr) {}
        void insert(T value, int (*cmp)(T, T));
        SharedPtr<SmartSequence<T>> traverse();
    };

    template <typename T>
    void BinarySearchTree<T>::insert(T value, int (*cmp)(T, T)) {
        if (!this->value) {
            this->value = make_unique<T>(value);
            return;
        }

        if (cmp(value, *this->value) < 0) {
            if (!left) {
                left = make_unique<BinarySearchTree<T>>();
            }
            left->insert(value, cmp);
        } else {
            if (!right) {
                right = make_unique<BinarySearchTree<T>>();
            }
            right->insert(value, cmp);
        }
    }

    template <typename T>
    SharedPtr<SmartSequence<T>> BinarySearchTree<T>::traverse() {
        if (value == nullptr) {
            return SharedPtr<SmartSequence<T>>(new SmartListSequence<T>());
        }
        SharedPtr<SmartSequence<T>> sequence(new SmartListSequence<T>());

        if(left) sequence = sequence->concat(*(left->traverse()));
        sequence->append(*value);
        if(right) sequence = sequence->concat(*(right->traverse()));

        return sequence;
    }

    template <typename T>
    class InsertionByTreeSorter : public BaseSorter<T> {
    private:
        using BaseSorter<T>::arr;
        using BaseSorter<T>::cmp;

    public:
        InsertionByTreeSorter(SharedPtr<SmartSequence<T>> arr, int (*cmp)(T, T)) : BaseSorter<T>(arr, cmp) {}
        void sort();
    };

    template <typename T>
    void InsertionByTreeSorter<T>::sort() {
        BinarySearchTree<T> tree;
        for (int i = 0; i < arr->getSize(); i++) {
            tree.insert(arr->get(i), cmp);
        }

        auto sorted = tree.traverse();
        for(int i = 0; i < arr->getSize(); i++) {
            (*arr)[i] = std::move((*sorted)[i]);
        }
    }
} // namespace sem3
