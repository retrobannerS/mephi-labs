#ifndef LAB3_N_ARY_TREE_HPP
#define LAB3_N_ARY_TREE_HPP

#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include <stdexcept>
#include <iostream>
#include <string>

using namespace lab2;
using namespace std;

namespace lab4 {

    template <typename T>
    class N_ary_tree {
    private:
        T data;
        int max_subtrees;
        N_ary_tree<T>* parent;
        ArraySequence<N_ary_tree<T>*>* subtrees;

        Sequence<T> *traverse_nlr() const;
        Sequence<T> *traverse_nrl() const;
        Sequence<T> *traverse_lrn() const;
        Sequence<T> *traverse_rln() const;
    public:
        enum TraverseType {
            NLR,
            NRL,
            LRN,
            RLN,
        };

        N_ary_tree(const T& item, int arity);
        N_ary_tree(const N_ary_tree<T>& other);
        ~N_ary_tree();

        N_ary_tree<T>& operator=(const N_ary_tree<T>& other);

        [[nodiscard]] int arity() const;
        [[nodiscard]] int current_subtrees() const;
        [[nodiscard]] int size() const;
        [[nodiscard]] int height() const;

        T value() const;
        void set(const T& item);

        void add_subtree(N_ary_tree<T>* subtree);
        void add_subtree(const T& item);
        N_ary_tree<T>& get_subtree(int index) const;
        N_ary_tree<T>& get_parent() const;
        void delete_subtree(int index);

        [[nodiscard]] string to_string() const;
        string to_string(TraverseType type) const;
        string to_string_for_ui() const;

        N_ary_tree<T> &operator[](int index);
        friend ostream& operator<<(ostream &os, const N_ary_tree<T> &tree) {
            os << tree.to_string();
            return os;
        }
        friend bool operator ==(const N_ary_tree<T>& lhs, const N_ary_tree<T>& rhs) {
            if(lhs.data != rhs.data) {
                return false;
            }
            if(lhs.current_subtrees() != rhs.current_subtrees()) {
                return false;
            }
            if(lhs.max_subtrees != rhs.max_subtrees) {
                return false;
            }
            for(int i = 0; i < lhs.current_subtrees(); i++) {
                if(*lhs.subtrees->Get(i) != *rhs.subtrees->Get(i)) {
                    return false;
                }
            }

            return true;
        }
        friend bool operator !=(const N_ary_tree<T>& lhs, const N_ary_tree<T>& rhs) {
            if(lhs.data != rhs.data) {
                return true;
            }
            if(lhs.current_subtrees() != rhs.current_subtrees()) {
                return true;
            }
            if(lhs.max_subtrees != rhs.max_subtrees) {
                return true;
            }
            for(int i = 0; i < lhs.current_subtrees(); i++) {
                if(*lhs.subtrees->Get(i) != *rhs.subtrees->Get(i)) {
                    return true;
                }
            }

            return false;
        }

        N_ary_tree<T> *map(T (*f)(T)) const;
        N_ary_tree<T> *where(bool (*f)(T)) const;

        bool contains(const T& item) const;
        bool contains(const N_ary_tree<T>& subtree) const;
        int item_count(const T& item) const;
        Sequence<T> *traverse() const;
        Sequence<T> *traverse(TraverseType type) const;
    };

    template<typename T>
    Sequence<T> *N_ary_tree<T>::traverse_nlr() const {
        auto *result = new ListSequence<T>();
        result->PushBack(data);
        for(int i = 0; i < subtrees->GetSize(); i++) {
            Sequence<T> *subtree_result = subtrees->Get(i)->traverse_nlr();
            for(int j = 0; j < subtree_result->GetSize(); j++) {
                result->PushBack(subtree_result->Get(j));
            }
            delete subtree_result;
        }
        return result;
    }

    template<typename T>
    Sequence<T> *N_ary_tree<T>::traverse_nrl() const {
        auto *result = new ListSequence<T>();
        result->PushBack(data);
        for(int i = subtrees->GetSize() - 1; i >= 0; i--) {
            Sequence<T> *subtree_result = subtrees->Get(i)->traverse_nrl();
            for(int j = 0; j < subtree_result->GetSize(); j++) {
                result->PushBack(subtree_result->Get(j));
            }
            delete subtree_result;
        }
        return result;
    }

    template<typename T>
    Sequence<T> *N_ary_tree<T>::traverse_lrn() const {
        auto *result = new ListSequence<T>();
        for(int i = 0; i < subtrees->GetSize(); i++) {
            Sequence<T> *subtree_result = subtrees->Get(i)->traverse_lrn();
            for(int j = 0; j < subtree_result->GetSize(); j++) {
                result->PushBack(subtree_result->Get(j));
            }
            delete subtree_result;
        }
        result->PushBack(data);
        return result;
    }

    template<typename T>
    Sequence<T> *N_ary_tree<T>::traverse_rln() const {
        auto *result = new ListSequence<T>();
        for(int i = subtrees->GetSize() - 1; i >= 0; i--) {
            Sequence<T> *subtree_result = subtrees->Get(i)->traverse_rln();
            for(int j = 0; j < subtree_result->GetSize(); j++) {
                result->PushBack(subtree_result->Get(j));
            }
            delete subtree_result;
        }
        result->PushBack(data);
        return result;
    }

    template<typename T>
    N_ary_tree<T>::N_ary_tree(const T& item, int arity) : max_subtrees(arity) {
        if(max_subtrees < 1) {
            throw invalid_argument("Invalid arity!");
        }
        data = item;
        parent = nullptr;
        subtrees = new ArraySequence<N_ary_tree<T>*>();
        subtrees->Reserve(arity);
    }

    template<typename T>
    N_ary_tree<T>::N_ary_tree(const N_ary_tree<T>& other) {
        data = other.data;
        max_subtrees = other.max_subtrees;
        parent = other.parent;
        subtrees = new ArraySequence<N_ary_tree<T>*>();
        subtrees->Reserve(max_subtrees);
        for(int i = 0; i < other.subtrees->GetSize(); i++) {
            subtrees->PushBack(new N_ary_tree<T>(*other.subtrees->Get(i)));
        }
    }

    template<typename T>
    N_ary_tree<T>::~N_ary_tree() {
        for(int i = 0; i < subtrees->GetSize(); i++) {
            delete subtrees->Get(i);
        }
        delete subtrees;
    }

    template<typename T>
    N_ary_tree<T>& N_ary_tree<T>::operator=(const N_ary_tree<T>& other) {
        if(this != &other) {
            for(int i = 0; i < subtrees->GetSize(); i++) {
                delete subtrees->Get(i);
            }
            delete subtrees;
            data = other.data;
            max_subtrees = other.max_subtrees;
            parent = other.parent;
            subtrees->Reserve(max_subtrees);
            for(int i = 0; i < other.subtrees->GetSize(); i++) {
                subtrees->PushBack(new N_ary_tree<T>(*other.subtrees->Get(i)));
            }
        }
        return *this;
    }

    template<typename T>
    int N_ary_tree<T>::arity() const {
        return max_subtrees;
    }

    template<typename T>
    int N_ary_tree<T>::current_subtrees() const {
        return subtrees->GetSize();
    }

    template<typename T>
    int N_ary_tree<T>::size() const {
        int size = 1;
        for(int i = 0; i < subtrees->GetSize(); i++) {
            size += subtrees->Get(i)->size();
        }
        return size;
    }

    template<typename T>
    int N_ary_tree<T>::height() const {
        int height = 0;
        for(int i = 0; i < subtrees->GetSize(); i++) {
            int subtree_height = subtrees->Get(i)->height();
            height = max(height, subtree_height);
        }
        return height + 1;
    }

    template<typename T>
    T N_ary_tree<T>::value() const {
        return data;
    }

    template<typename T>
    void N_ary_tree<T>::set(const T& item) {
        data = item;
    }

    template<typename T>
    void N_ary_tree<T>::add_subtree(N_ary_tree<T>* subtree) {
        if(subtrees->GetSize() == max_subtrees) {
            throw out_of_range("No more space for subtrees!");
        }
        if(max_subtrees != subtree->max_subtrees) {
            throw invalid_argument("Invalid arity!");
        }
        subtrees->PushBack(new N_ary_tree<T>(*subtree));
        subtree->parent = this;
    }

    template<typename T>
    void N_ary_tree<T>::add_subtree(const T& item) {
        if(subtrees->GetSize() == max_subtrees) {
            throw out_of_range("No more space for subtrees!");
        }
        subtrees->PushBack(new N_ary_tree<T>(item, max_subtrees));
        subtrees->Get(subtrees->GetSize() - 1)->parent = this;
    }

    template<typename T>
    N_ary_tree<T>& N_ary_tree<T>::get_subtree(int index) const {
        if(index < 0 || index >= subtrees->GetSize()) {
            throw out_of_range("Index out of range!");
        }
        return *subtrees->Get(index);
    }

    template<typename T>
    N_ary_tree<T>& N_ary_tree<T>::get_parent() const {
        if(parent == nullptr) {
            throw out_of_range("No parent!");
        }
        return *parent;
    }

    template<typename T>
    void N_ary_tree<T>::delete_subtree(int index) {
        if(index < 0 || index >= subtrees->GetSize()) {
            throw out_of_range("Index out of range!");
        }
        delete subtrees->Get(index);
        subtrees->PopFrom(index);
    }

    template<typename T>
    string N_ary_tree<T>::to_string() const {
        return to_string(NLR);
    }

    template<typename T>
    string N_ary_tree<T>::to_string(TraverseType type) const {
        Sequence<T> *to_sequence;
        switch (type) {
            case NLR:
                to_sequence = traverse_nlr();
                break;
            case NRL:
                to_sequence = traverse_nrl();
                break;
            case LRN:
                to_sequence = traverse_lrn();
                break;
            case RLN:
                to_sequence = traverse_rln();
                break;
            default:
                throw invalid_argument("Invalid traverse type!");
        }
        string result;
        for(int i = 0; i < to_sequence->GetSize(); i++) {
            result += std::to_string(to_sequence->Get(i)) + " ";
        }
        delete to_sequence;
        return result;
    }

    template<typename T>
    string N_ary_tree<T>::to_string_for_ui() const {
        string result;
        result += std::to_string(data) + " ";
        if (current_subtrees() > 0) {
            result += "( ";
            for (int i = 0; i < current_subtrees(); i++) {
                result += subtrees->Get(i)->to_string();
            }
            result += ") ";
        }
    }

    template<typename T>
    N_ary_tree<T>& N_ary_tree<T>::operator[](int index) {
        return *(subtrees->operator[](index));
    }

    template <typename T>
    N_ary_tree<T> *N_ary_tree<T>::map(T (*f)(T)) const {
        auto *new_tree = new N_ary_tree<T>(f(data), max_subtrees);

        for (int i = 0; i < current_subtrees(); i++) {
            auto *mapped_subtree = subtrees->Get(i)->map(f);
            new_tree->add_subtree(mapped_subtree);
            delete mapped_subtree;
        }

        return new_tree;
    }

    template <typename T>
    N_ary_tree<T> *N_ary_tree<T>::where(bool (*f)(T)) const {
        if(!f(data)) {
            return nullptr;
        }
        auto *new_tree = new N_ary_tree<T>(data, max_subtrees);

        for (int i = 0; i < current_subtrees(); i++) {
            if (f(subtrees->Get(i)->value())) {
                auto *filtered_subtree = subtrees->Get(i)->where(f);
                new_tree->add_subtree(filtered_subtree);
                delete filtered_subtree;
            }
        }

        return new_tree;
    }

    template <typename T>
    bool N_ary_tree<T>::contains(const T &item) const {
        if (this->data == item) {
            return true;
        }

        for (int i = 0; i < this->current_subtrees(); i++) {
            if (this->subtrees->Get(i)->contains(item)) {
                return true;
            }
        }

        return false;
    }

    template <typename T>
    bool N_ary_tree<T>::contains(const N_ary_tree<T> &subtree) const {
        if (subtree == *this)
            return true;

        for (int i = 0; i < current_subtrees(); ++i)
            if (get_subtree(i).contains(subtree))
                return true;

        return false;
    }

    template<typename T>
    int N_ary_tree<T>::item_count(const T &item) const {
        int count = 0;
        if (this->data == item) {
            count++;
        }

        for (int i = 0; i < this->current_subtrees(); i++) {
            count += this->subtrees->Get(i)->item_count(item);
        }

        return count;
    }

    template<typename T>
    Sequence<T> *N_ary_tree<T>::traverse() const {
        return traverse_nlr();
    }

    template<typename T>
    Sequence<T> *N_ary_tree<T>::traverse(TraverseType type) const {
        switch (type) {
            case NLR:
                return traverse_nlr();
            case NRL:
                return traverse_nrl();
            case LRN:
                return traverse_lrn();
            case RLN:
                return traverse_rln();
            default:
                throw invalid_argument("Invalid traverse type!");
        }
    }
} // lab4

#endif //LAB3_N_ARY_TREE_HPP
