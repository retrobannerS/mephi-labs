#ifndef LAB3_SET_HPP
#define LAB3_SET_HPP
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "IEnumerable.hpp"
#include <string>
#include <stdexcept>

using namespace lab2;
using namespace std;

namespace lab3 {

    template<typename T>
    class Set : public IEnumerable<T> {
    private:
        using IEnumerable<T>::sequence;
        int power_;
        void sort();
    public:
        Set();
        Set(const Set<T> &other);
        ~Set();

        Set<T> &operator=(const Set<T> &other);
        friend ostream &operator<<(ostream &out, const Set<T> &set) {
            out << "{";
            for (int i = 0; i < set.power_; ++i) {
                out << set.sequence->Get(i);
            }
            out << "\b\b}";
            return out;
        }

        [[nodiscard]] int power() const;
        [[nodiscard]] bool empty() const;
        [[nodiscard]] bool contains(const T &item) const;
        void add(const T &item);
        void remove(const T &item);
        void clear();

        Set<T> map(T (*func)(const T &)) const;
        Set<T> where(bool (*func)(const T &)) const;
        Set<T> union_with(const Set<T> &other) const;
        Set<T> intersection_with(const Set<T> &other) const;
        Set<T> difference_with(const Set<T> &other) const;
        bool is_subset_of(const Set<T> &other) const;

        bool operator ==(const Set<T> &other) const;
    };


    template<typename T>
    void Set<T>::sort() {
        for (int i = 1; i < sequence->GetSize(); ++i) {
            T key = sequence->Get(i);
            int j = i - 1;
            while (j >= 0 && sequence->Get(j) > key) {
                sequence->Set(j + 1, sequence->Get(j));
                j--;
            }
            sequence->Set(j + 1, key);
        }
    }

    template<typename T>
    Set<T>::Set() {
        sequence = new ArraySequence<T>();
        power_ = 0;
    }

    template<typename T>
    Set<T>::Set(const Set<T> &other) {
        sequence = new ArraySequence<T>(other.sequence);
        power_ = other.power_;
    }

    template<typename T>
    Set<T>::~Set() = default;

    template<typename T>
    Set<T> &Set<T>::operator=(const Set<T> &other) {
        if (this != &other) {
            delete sequence;
            sequence = new ArraySequence<T>(other.sequence);
            power_ = other.power_;
        }
        return *this;
    }

    template<typename T>
    int Set<T>::power() const {
        return power_;
    }

    template<typename T>
    bool Set<T>::empty() const {
        return power_ == 0;
    }

    template<typename T>
    bool Set<T>::contains(const T &item) const {
        for (int i = 0; i < power_; ++i) {
            if (sequence->Get(i) == item) {
                return true;
            }
        }
        return false;
    }

    template<typename T>
    void Set<T>::add(const T &item) {
        if (!contains(item)) {
            sequence->PushBack(item);
            power_++;
            sort();
        }
    }

    template<typename T>
    void Set<T>::remove(const T &item) {
        if (contains(item)) {
            for (int i = 0; i < power_; ++i) {
                if (sequence->Get(i) == item) {
                    sequence->PopFrom(i);
                    power_--;
                    break;
                }
            }
        }
    }

    template<typename T>
    void Set<T>::clear() {
        delete sequence;
        sequence = new ArraySequence<T>();
        power_ = 0;
    }

    template<typename T>
    Set<T> Set<T>::map(T (*func)(const T &)) const {
        Set<T> result;
        for (int i = 0; i < power_; ++i) {
            result.add(func(sequence->Get(i)));
        }
        return result;
    }

    template<typename T>
    Set<T> Set<T>::where(bool (*func)(const T &)) const {
        Set<T> result;
        for (int i = 0; i < power_; ++i) {
            if (func(sequence->Get(i))) {
                result.add(sequence->Get(i));
            }
        }
        return result;
    }

    template<typename T>
    Set<T> Set<T>::union_with(const Set<T> &other) const {
        Set<T> result(*this);
        for (int i = 0; i < other.power_; ++i) {
            result.add(other.sequence->Get(i));
        }
        return result;
    }

    template<typename T>
    Set<T> Set<T>::intersection_with(const Set<T> &other) const {
        Set<T> result;
        for (int i = 0; i < power_; ++i) {
            if (other.contains(sequence->Get(i))) {
                result.add(sequence->Get(i));
            }
        }
        return result;
    }

    template<typename T>
    Set<T> Set<T>::difference_with(const Set<T> &other) const {
        Set<T> result;
        for (int i = 0; i < power_; ++i) {
            if (!other.contains(sequence->Get(i))) {
                result.add(sequence->Get(i));
            }
        }
        return result;
    }

    template<typename T>
    bool Set<T>::is_subset_of(const Set<T> &other) const {
        for (int i = 0; i < power_; ++i) {
            if (!other.contains(sequence->Get(i))) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    bool Set<T>::operator==(const Set<T> &other) const {
        if (power_ != other.power_) {
            return false;
        }
        for (int i = 0; i < power_; ++i) {
            if (!other.contains(sequence->Get(i))) {
                return false;
            }
        }
        return true;
    }
} // lab3

#endif //LAB3_SET_HPP
