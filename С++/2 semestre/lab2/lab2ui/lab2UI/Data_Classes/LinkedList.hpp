#ifndef LAB2CORRECT2_LINKEDLIST_HPP
#define LAB2CORRECT2_LINKEDLIST_HPP

namespace lab2 {

    template <typename T1>
    class LinkedList {
    private:
        template <typename T2>
        class Node {
        public:
            T2 data;
            Node *next = nullptr;
            Node() = default;
            explicit Node(const T2 &data) : data(data) {}
            Node(const T2 &data, Node *next) : data(data), next(next) {}
        };

        Node<T1> *head = nullptr;
        Node<T1> *tail = nullptr;
        size_t size = 0;
    public:
        LinkedList();
        explicit LinkedList(int size);
        LinkedList(int size, const T1 &item);
        LinkedList(int size, const T1 *items);

        LinkedList(const LinkedList<T1> &other);

        ~LinkedList();

        T1 GetFirst() const;
        T1 GetLast() const;
        T1 Get(int index) const;
        [[nodiscard]] size_t GetSize() const;
        LinkedList<T1> GetSubList(int start, int end) const;

        void Set(int index, const T1 &item);
        void Set(int start, int count, const T1 &item);
        void PushBack(const T1 &item);
        void PushFront(const T1 &item);
        void InsertAt(int index, const T1 &item);
        void PopFrom(int index);
        void PopBack();
        void PopFront();

        LinkedList<T1> operator +(const LinkedList<T1> &another) const;
        LinkedList<T1> &operator =(const LinkedList<T1> &other);
        T1 &operator [](int index);

        LinkedList<T1> Concat(const LinkedList<T1> &another) const;
    };

} //lab2

#include "LinkedList.cpp"
#endif //LAB2CORRECT2_LINKEDLIST_HPP
