#pragma once

#include "LinkedList.hpp"
#include "SharedPtr.hpp"
#include "WeakPtr.hpp"
#include <stdexcept>

namespace sem3 {

    template <typename T>
    class SmartLinkedList {
    private:
        class Node {
        public:
            T data;
            SharedPtr<Node> next;
            WeakPtr<Node> prev;
            Node(T data, SharedPtr<Node> next, WeakPtr<Node> prev) : data(data), next(next), prev(prev){};
        };

        SharedPtr<Node> head;
        SharedPtr<Node> tail;
        int size;

    public:
        SmartLinkedList();
        explicit SmartLinkedList(int size);
        SmartLinkedList(int size, const T &item);
        SmartLinkedList(int size, const T *items);
        SmartLinkedList(int size, const SharedPtr<T[]> &items);
        SmartLinkedList(const SmartLinkedList &other);
        SmartLinkedList(SmartLinkedList &&other);
        SmartLinkedList(const lab2::LinkedList<T> &other);

        ~SmartLinkedList() = default;

        SmartLinkedList<T> &operator=(const SmartLinkedList &other);
        SmartLinkedList<T> &operator=(SmartLinkedList &&other);
        SmartLinkedList<T> &operator=(const lab2::LinkedList<T> &other);

        T get(int index) const;
        T getFirst() const;
        T getLast() const;
        [[nodiscard]] int getSize() const;
        SmartLinkedList<T> getSubList(int startIndex, int endIndex) const;

        void set(int index, const T &item);
        void set(int startIndex, int endIndex, const T &item);

        void append(const T &item);
        void prepend(const T &item);
        void insertAt(int index, const T &item);
        void removeAt(int index);
        void removeFirst();
        void removeLast();

        T &operator[](int index);
        SmartLinkedList<T> operator+(const SmartLinkedList<T> &other) const;

        SmartLinkedList<T> concat(const SmartLinkedList<T> &other) const;
    };

    template <typename T>
    SmartLinkedList<T>::SmartLinkedList() : head(SharedPtr<Node>()), tail(SharedPtr<Node>()), size(0) {}

    template <typename T>
    SmartLinkedList<T>::SmartLinkedList(int size) : SmartLinkedList(size, T()) {}

    template <typename T>
    SmartLinkedList<T>::SmartLinkedList(int size, const T &item) : SmartLinkedList() {
        if (size < 0) {
            throw std::invalid_argument("Size must be non-negative");
        }
        for (int i = 0; i < size; i++) {
            append(item);
        }
    }

    template <typename T>
    SmartLinkedList<T>::SmartLinkedList(int size, const T *items) : SmartLinkedList() {
        if (size < 0) {
            throw std::invalid_argument("Size must be non-negative");
        }
        for (int i = 0; i < size; i++) {
            append(items[i]);
        }
    }

    template <typename T>
    SmartLinkedList<T>::SmartLinkedList(int size, const SharedPtr<T[]> &items) : SmartLinkedList() {
        if (size < 0) {
            throw std::invalid_argument("Size must be non-negative");
        }
        for (int i = 0; i < size; i++) {
            append(items[i]);
        }
    }

    template <typename T>
    SmartLinkedList<T>::SmartLinkedList(const SmartLinkedList &other) : SmartLinkedList() {
        for (int i = 0; i < other.size; i++) {
            append(other.get(i));
        }
    }

    template <typename T>
    SmartLinkedList<T>::SmartLinkedList(SmartLinkedList &&other)
        : head(other.head), tail(other.tail), size(other.size) {
        other.head = SharedPtr<Node>();
        other.tail = SharedPtr<Node>();
        other.size = 0;
    }

    template <typename T>
    SmartLinkedList<T>::SmartLinkedList(const lab2::LinkedList<T> &other) : SmartLinkedList() {
        for (int i = 0; i < other.GetSize(); i++) {
            append(other.Get(i));
        }
    }

    template <typename T>
    SmartLinkedList<T> &SmartLinkedList<T>::operator=(const SmartLinkedList &other) {
        if (this == &other) {
            return *this;
        }
        head = SharedPtr<Node>();
        tail = SharedPtr<Node>();
        size = 0;
        for (int i = 0; i < other.size; i++) {
            append(other.get(i));
        }
        return *this;
    }

    template <typename T>
    SmartLinkedList<T> &SmartLinkedList<T>::operator=(SmartLinkedList &&other) {
        if (this == &other) {
            return *this;
        }
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.head = SharedPtr<Node>();
        other.tail = SharedPtr<Node>();
        other.size = 0;
        return *this;
    }

    template <typename T>
    SmartLinkedList<T> &SmartLinkedList<T>::operator=(const lab2::LinkedList<T> &other) {
        head = SharedPtr<Node>();
        tail = SharedPtr<Node>();
        size = 0;
        for (int i = 0; i < other.GetSize(); i++) {
            append(other.Get(i));
        }
        return *this;
    }

    template <typename T>
    T SmartLinkedList<T>::get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        SharedPtr<Node> current;
        if (index <= size / 2) {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = size - 1; i > index; i--) {
                current = current->prev.lock();
            }
        }
        return current->data;
    }

    template <typename T>
    T SmartLinkedList<T>::getFirst() const {
        if (size == 0) {
            throw std::out_of_range("Index out of range");
        }
        return head->data;
    }

    template <typename T>
    T SmartLinkedList<T>::getLast() const {
        if (size == 0) {
            throw std::out_of_range("Index out of range");
        }
        return tail->data;
    }

    template <typename T>
    int SmartLinkedList<T>::getSize() const {
        return size;
    }

    template <typename T>
    SmartLinkedList<T> SmartLinkedList<T>::getSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 or startIndex >= size or endIndex < 0 or endIndex > size) {
            throw std::out_of_range("Index out of range");
        } else if (startIndex > endIndex) {
            throw std::invalid_argument("Start index must be less than end index");
        } else {
            SmartLinkedList<T> result;
            for (int i = startIndex; i < endIndex; i++) {
                result.append(this->get(i));
            }
            return result;
        }
    }

    template <typename T>
    void SmartLinkedList<T>::set(int index, const T &item) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        (*this)[index] = item;
    }

    template <typename T>
    void SmartLinkedList<T>::set(int startIndex, int endIndex, const T &item) {
        if (startIndex < 0 or startIndex >= size or endIndex < 0 or endIndex > size) {
            throw std::out_of_range("Index out of range");
        } else if (startIndex > endIndex) {
            throw std::invalid_argument("Start index must be less than end index");
        } else {
            for (int i = startIndex; i < endIndex; i++) {
                (*this)[i] = item;
            }
        }
    }

    template <typename T>
    void SmartLinkedList<T>::append(const T &item) {
        tail = sem3::make_shared<Node>(item, SharedPtr<Node>(), WeakPtr<Node>(tail));
        if (size == 0) {
            head = tail;
        } else {
            tail->prev.lock()->next = tail;
        }
        size++;
    }

    template <typename T>
    void SmartLinkedList<T>::prepend(const T &item) {
        head = sem3::make_shared<Node>(item, head, WeakPtr<Node>());
        if (size == 0) {
            tail = head;
        } else {
            head->next->prev = head;
        }
        size++;
    }

    template <typename T>
    void SmartLinkedList<T>::insertAt(int index, const T &item) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) {
            prepend(item);
        } else if (index == size) {
            append(item);
        } else {
            SharedPtr<Node> current;
            if (index <= size / 2) {
                current = head;
                for (int i = 0; i < index - 1; i++) {
                    current = current->next;
                }
            } else {
                current = tail;
                for (int i = size - 1; i > index - 1; i--) {
                    current = current->prev.lock();
                }
            }
            current->next = sem3::make_shared<Node>(item, current->next, WeakPtr<Node>(current));
            current->next->next->prev = WeakPtr<Node>(current->next);
            size++;
        }
    }

    template <typename T>
    void SmartLinkedList<T>::removeAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) {
            removeFirst();
        } else if (index == size - 1) {
            removeLast();
        } else {
            SharedPtr<Node> current;
            if (index <= size / 2) {
                current = head;
                for (int i = 0; i < index; i++) {
                    current = current->next;
                }
            } else {
                current = tail;
                for (int i = size - 1; i > index; i--) {
                    current = current->prev.lock();
                }
            }
            current->next->prev = current->prev;
            current->prev.lock()->next = current->next;
            size--;
        }
    }

    template <typename T>
    void SmartLinkedList<T>::removeFirst() {
        if (size == 0) {
            throw std::out_of_range("Index out of range");
        }
        SharedPtr<Node> tmp = head;
        head = tmp->next;
        if (size == 1) {
            tail = nullptr;
        }
        head->prev = nullptr;
        size--;
    }

    template <typename T>
    void SmartLinkedList<T>::removeLast() {
        if (size == 0) {
            throw std::out_of_range("Index out of range");
        }
        tail = tail->prev.lock();
        if (size == 1) {
            head = SharedPtr<Node>();
        } else {
            tail->next = nullptr;
        }
        size--;
    }

    template <typename T>
    T &SmartLinkedList<T>::operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        SharedPtr<Node> current;
        if (index <= size / 2) {
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            current = tail;
            for (int i = size - 1; i > index; i--) {
                current = current->prev.lock();
            }
        }
        return current->data;
    }

    template <typename T>
    SmartLinkedList<T> SmartLinkedList<T>::operator+(const SmartLinkedList<T> &other) const {
        return concat(other);
    }

    template <typename T>
    SmartLinkedList<T> SmartLinkedList<T>::concat(const SmartLinkedList<T> &other) const {
        SmartLinkedList<T> result = *this;
        for (int i = 0; i < other.size; i++) {
            result.append(other.get(i));
        }
        return result;
    }

} // namespace sem3
