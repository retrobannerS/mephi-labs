#ifndef LAB2CORRECT2_LINKEDLIST_HPP
#define LAB2CORRECT2_LINKEDLIST_HPP
#include <stdexcept>

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

    template <typename T>
    LinkedList<T>::LinkedList() = default;

    template <typename T>
    LinkedList<T>::LinkedList(int size) : LinkedList(size, T()) {
    }

    template <typename T>
    LinkedList<T>::LinkedList(int size, const T &item) {
        if(size < 0) {
            throw std::invalid_argument("Invalid size!");
        }
        for(int i = 0; i != size; ++i) {
            this->PushBack(item);
        }
    }

    template <typename T>
    LinkedList<T>::LinkedList(int size, const T *items) {
        if(size < 0) {
            throw std::invalid_argument("Invalid size!");
        }
        for(int i = 0; i != size; ++i) {
            this->PushBack(items[i]);
        }
    }

    template <typename T>
    LinkedList<T>::LinkedList(const LinkedList<T> &other) {
        for(int i = 0; i != other.GetSize(); ++i) {
            this->PushBack(other.Get(i));
        }
    }

    template <typename T>
    LinkedList<T>::~LinkedList() {
        Node <T> *ptr = this->head;
        while(ptr) {
            Node <T> *prev = ptr;
            ptr = ptr->next;
            delete prev;
        }
        this->tail = this->head = nullptr;
    }

    template <typename T>
    T LinkedList<T>::GetFirst() const {
        if(!this->head) {
            throw std::out_of_range("Index out of range!");
        }
        return this->head->data;
    }

    template <typename T>
    T LinkedList<T>::GetLast() const {
        if(!this->tail) {
            throw std::out_of_range("Index out of range!");
        }
        return this->tail->data;
    }

    template <typename T>
    T LinkedList<T>::Get(int index) const {
        if(index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range!");
        }
        Node <T> *ptr = this->head;
        for(int i = 0; i != index; ++i) {
            ptr = ptr->next;
        }
        return ptr->data;
    }

    template <typename T>
    size_t LinkedList<T>::GetSize() const {
        return this->size;
    }

    template <typename T>
    LinkedList<T> LinkedList<T>::GetSubList(int start, int end) const {
        if(start < 0 || start >= this->size || end < 0 || end >= this->size || start > end) {
            throw std::out_of_range("Index out of range!");
        } else {
            LinkedList<T> result;
            for(int i = start; i != end + 1; ++i) {
                result.PushBack(this->Get(i));
            }
            return result;
        }
    }

    template <typename T>
    void LinkedList<T>::Set(int index, const T &item) {
        if(index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range!");
        }
        Node <T> *ptr = this->head;
        for(int i = 0; i != index; ++i) {
            ptr = ptr->next;
        }
        ptr->data = item;
    }

    template <typename T>
    void LinkedList<T>::Set(int start, int count, const T &item) {
        if(start < 0 || start >= this->size || count < 0 || start + count > this->size) {
            throw std::out_of_range("Index out of range!");
        }
        for(int i = start; i != start + count; ++i) {
            this->Set(i, item);
        }
    }

    template <typename T>
    void LinkedList<T>::PushBack(const T &item) {
        if(!this->head) {
            this->tail = this->head = new Node<T>(item);
        } else {
            this->tail = this->tail->next = new Node<T>(item);
        }
        this->size++;
    }

    template <typename T>
    void LinkedList<T>::PushFront(const T &item) {
        if(!this->head) {
            this->tail = this->head = new Node<T>(item);
        } else {
            this->head = new Node<T>(item, this->head);
        }
        this->size++;
    }

    template <typename T>
    void LinkedList<T>::InsertAt(int index, const T &item) {
        if(index < 0 || index > this->size) {
            throw std::out_of_range("Index out of range!");
        } else if(index == 0) {
            this->PushFront(item);
        } else if(index == this->size) {
            this->PushBack(item);
        } else {
            Node <T> *ptr = this->head;
            for(int i = 0; i + 1 != index; ++i) {
                ptr = ptr->next;
            }
            ptr->next = new Node<T>(item, ptr->next);
            this->size++;
        }
    }

    template <typename T>
    void LinkedList<T>::PopFrom(int index) {
        if(index < 0 || index >= this->GetSize()) {
            throw std::out_of_range("Index out of range!");
        }
        Node<T> *temp = head;
        if (index == 0) {
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            delete temp;
        } else {
            Node<T> *prev;
            for (int i = 0; i < index; i++) {
                prev = temp;
                temp = temp->next;
            }
            prev->next = temp->next;
            if (temp->next == nullptr) {
                tail = prev;
            }
            delete temp;
        }
        this->size--;
    }

    template <typename T>
    void LinkedList<T>::PopBack() {
        if(!this->head) {
            throw std::out_of_range("Index out of range!");
        }
        this->PopFrom(this->size - 1);
    }

    template <typename T>
    void LinkedList<T>::PopFront() {
        if(!this->head) {
            throw std::out_of_range("Index out of range!");
        }
        this->PopFrom(0);
    }

    template <typename T>
    T &LinkedList<T>::operator [](int index) {
        if(index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range!");
        } else {
            Node <T> *ptr = this->head;
            for(int i = 0; i != index; ++i) {
                ptr = ptr->next;
            }
            return ptr->data;
        }
    }

    template <typename T>
    LinkedList<T> &LinkedList<T>::operator =(const LinkedList<T> &other) {
        if(this != &other) {
            Node <T> *ptr = this->head;
            while(ptr) {
                Node <T> *prev = ptr;
                ptr = ptr->next;
                delete prev;
            }
            this->tail = this->head = nullptr;
            this->size = 0;
            for(int i = 0; i != other.GetSize(); ++i) {
                this->PushBack(other.Get(i));
            }
        }
        return *this;
    }

    template <typename T>
    LinkedList<T> LinkedList<T>::operator +(const LinkedList<T> &another) const {
        return this->Concat(another);
    }

    template <typename T>
    LinkedList<T> LinkedList<T>::Concat(const LinkedList<T> &other) const {
        LinkedList<T> result(*this);
        for(int i = 0; i != other.GetSize(); ++i) {
            result.PushBack(other.Get(i));
        }
        return result;
    }

} //lab2
#endif //LAB2CORRECT2_LINKEDLIST_HPP
