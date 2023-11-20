#pragma once
#include "ListSequence.hpp"
#include "containers/SmartSequence.hpp"
#include "data_classes/SmartDynamicArray.hpp"
#include "data_classes/SmartLinkedList.hpp"
#include "smart_pointers/UniquePtr.hpp"
#include <stdexcept>

namespace sem3 {
    template <typename T>
    class SmartListSequence : public SmartSequence<T> {
    private:
        UniquePtr<SmartLinkedList<T>> list;

    public:
        SmartListSequence();
        explicit SmartListSequence(int size);
        SmartListSequence(int size, const T &item);
        SmartListSequence(int size, const T *items);
        explicit SmartListSequence(const SmartLinkedList<T> &list);
        explicit SmartListSequence(const SmartDynamicArray<T> &array);
        explicit SmartListSequence(const ListSequence<T> &list);
        explicit SmartListSequence(const SmartSequence<T> *sequence);
        explicit SmartListSequence(const Sequence<T> *sequence);

        ~SmartListSequence() override = default;

        SmartListSequence(const SmartListSequence<T> &other);
        SmartListSequence(SmartListSequence<T> &&other) noexcept;

        SmartListSequence<T> &operator=(const SmartListSequence<T> &other);
        SmartListSequence<T> &operator=(SmartListSequence<T> &&other) noexcept;

        T get(int index) const override;
        int getSize() const override;
        SharedPtr<SmartSequence<T>> getSubSequence(int startIndex, int endIndex) const override;

        void set(int index, const T &item) override;
        using SmartSequence<T>::set;

        void insertAt(int index, const T &item) override;
        void removeAt(int index) override;

        T &operator[](int index) override;
        SharedPtr<SmartSequence<T>> concat(const SmartSequence<T> &other) const override;

        void clear() override;

        SharedPtr<SmartSequence<T>> map(T (*mapper)(const T &)) const override;
        SharedPtr<SmartSequence<T>> where(bool (*predicate)(const T &)) const override;
        T reduce(T (*reducer)(const T &, const T &), const T &initialValue) const override;
    };

    template <typename T>
    SmartListSequence<T>::SmartListSequence() : list(make_unique<SmartLinkedList<T>>()) {}

    template <typename T>
    SmartListSequence<T>::SmartListSequence(int size) : list(make_unique<SmartLinkedList<T>>(size)) {}

    template <typename T>
    SmartListSequence<T>::SmartListSequence(int size, const T &item)
        : list(make_unique<SmartLinkedList<T>>(size, item)) {}

    template <typename T>
    SmartListSequence<T>::SmartListSequence(int size, const T *items)
        : list(make_unique<SmartLinkedList<T>>(size, items)) {}

    template <typename T>
    SmartListSequence<T>::SmartListSequence(const SmartLinkedList<T> &list)
        : list(sem3::make_unique<SmartLinkedList<T>>(list)) {}

    template <typename T>
    SmartListSequence<T>::SmartListSequence(const SmartDynamicArray<T> &array) {
        list = make_unique<SmartLinkedList<T>>();
        for (int i = 0; i < array.getSize(); i++) {
            this->list->append(array.get(i));
        }
    }

    template <typename T>
    SmartListSequence<T>::SmartListSequence(const ListSequence<T> &list) {
        this->list = make_unique<SmartLinkedList<T>>();
        for (int i = 0; i < list.GetSize(); i++) {
            this->list->append(list.Get(i));
        }
    }

    template <typename T>
    SmartListSequence<T>::SmartListSequence(const SmartSequence<T> *sequence) {
        list = make_unique<SmartLinkedList<T>>();
        for (int i = 0; i < sequence->getSize(); i++) {
            list->append(sequence->get(i));
        }
    }

    template <typename T>
    SmartListSequence<T>::SmartListSequence(const Sequence<T> *sequence) {
        list = make_unique<SmartLinkedList<T>>();
        for (int i = 0; i < sequence->GetSize(); i++) {
            list->append(sequence->Get(i));
        }
    }

    template <typename T>
    SmartListSequence<T>::SmartListSequence(const SmartListSequence<T> &other) {
        list = make_unique<SmartLinkedList<T>>();
        for (int i = 0; i < other.getSize(); i++) {
            list->append(other.get(i));
        }
    }

    template <typename T>
    SmartListSequence<T>::SmartListSequence(SmartListSequence<T> &&other) noexcept {
        list = std::move(other.list);
    }

    template <typename T>
    SmartListSequence<T> &SmartListSequence<T>::operator=(const SmartListSequence<T> &other) {
        if (this == &other) {
            return *this;
        }
        list = make_unique<SmartLinkedList<T>>();
        for (int i = 0; i < other.getSize(); i++) {
            list->append(other.get(i));
        }
        return *this;
    }

    template <typename T>
    SmartListSequence<T> &SmartListSequence<T>::operator=(SmartListSequence<T> &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        list = std::move(other.list);
        return *this;
    }

    template <typename T>
    T SmartListSequence<T>::get(int index) const {
        return list->get(index);
    }

    template <typename T>
    int SmartListSequence<T>::getSize() const {
        return list? list->getSize() : 0;
    }

    template <typename T>
    SharedPtr<SmartSequence<T>> SmartListSequence<T>::getSubSequence(int startIndex, int endIndex) const {
        SmartSequence<T> *new_list = new SmartListSequence<T>(list->getSubList(startIndex, endIndex));
        return SharedPtr<SmartSequence<T>>(new_list);
    }

    template <typename T>
    void SmartListSequence<T>::set(int index, const T &item) {
        list->set(index, item);
    }

    template <typename T>
    void SmartListSequence<T>::insertAt(int index, const T &item) {
        list->insertAt(index, item);
    }

    template <typename T>
    void SmartListSequence<T>::removeAt(int index) {
        list->removeAt(index);
    }

    template <typename T>
    T &SmartListSequence<T>::operator[](int index) {
        return list->operator[](index);
    }

    template <typename T>
    SharedPtr<SmartSequence<T>> SmartListSequence<T>::concat(const SmartSequence<T> &other) const {
        auto new_list = new SmartListSequence<T>();
        for (int i = 0; i < getSize(); i++) {
            new_list->append(get(i));
        }
        for (int i = 0; i < other.getSize(); i++) {
            new_list->append(other.get(i));
        }
        return SharedPtr<SmartSequence<T>>(new_list);
    }

    template <typename T>
    void SmartListSequence<T>::clear() {
        list.release();
    }

    template <typename T>
    SharedPtr<SmartSequence<T>> SmartListSequence<T>::map(T (*mapper)(const T &)) const {
        SmartSequence<T> *newSequence = new SmartListSequence<T>();
        for (int i = 0; i < getSize(); i++) {
            newSequence->append(mapper(get(i)));
        }
        return SharedPtr(newSequence);
    }

    template <typename T>
    SharedPtr<SmartSequence<T>> SmartListSequence<T>::where(bool (*predicate)(const T &)) const {
        SmartSequence<T> *newSequence = new SmartListSequence<T>();
        for (int i = 0; i < getSize(); i++) {
            if (predicate(get(i))) {
                newSequence->append(get(i));
            }
        }
        return SharedPtr<SmartSequence<T>>(newSequence);
    }

    template <typename T>
    T SmartListSequence<T>::reduce(T (*reducer)(const T &, const T &), const T &initialValue) const {
        T result = initialValue;
        for (int i = 0; i < getSize(); i++) {
            result = reducer(result, get(i));
        }
        return result;
    }
} // namespace sem3