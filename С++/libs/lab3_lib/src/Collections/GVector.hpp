#ifndef LAB3_GVECTOR_HPP
#define LAB3_GVECTOR_HPP
#include <utility>
#include <stdexcept>
#include <cmath>
#include "IEnumerable.hpp"
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "Options.hpp"

using namespace lab2;
using namespace std;

namespace lab3 {
    template<typename T>
    class GVector : public IEnumerable<T> {
    private:
        using IEnumerable<T>::sequence;
    public:
        explicit GVector(int dimensity);
        GVector(int dimensity, const T &item);
        GVector(int dimensity, const T *items);
        explicit GVector(const DynamicArray<T> &array);
        explicit GVector(const LinkedList<T> &list);
        explicit GVector(const Sequence<T> *sequence);
        GVector(const GVector<T> &other);
        //memory deletes in ~IEnumerable;
        ~GVector();

        T &operator[](int index);
        T Get(int index) const;

        GVector<T> &operator=(const GVector<T> &other);
        GVector<T> operator +(const GVector<T> &other);
        GVector<T> operator -(const GVector<T> &other);
        T operator*(const GVector<T> &other);
        friend GVector<T> operator *(const T &scalar, const GVector<T> &vector) {
            GVector<T> result(vector.dim());
            for (int i = 0; i < vector.dim(); ++i) {
                result[i] = vector.Get(i) * scalar;
            }
            return result;
        }
        friend GVector<T> operator *(const GVector<T> &vector, const T &scalar) {
            GVector<T> result(vector.dim());
            for (int i = 0; i < vector.dim(); ++i) {
                result[i] = vector.Get(i) * scalar;
            }
            return result;
        }
        [[nodiscard]] double module() const;

        [[nodiscard]] bool zero() const;
        [[nodiscard]] int dim() const;
        void clear();
    };

    template<typename T>
    bool GVector<T>::zero() const {
        bool result = true;
        for(int i = 0; i != dim(); ++i) {
            if (Get(i) != 0) {
                result = false;
                break;
            }
        }
        return result;
    }

    template<typename T>
    int GVector<T>::dim() const {
        return sequence->GetSize();
    }

    template<typename T>
    void GVector<T>::clear() {
        for(int i = 0; i != dim(); ++i) {
            sequence->Set(i, 0);
        }
    }

    template<typename T>
    GVector<T>::GVector(int dimensity) {
        sequence = new ArraySequence<T>(dimensity);
    }

    template<typename T>
    GVector<T>::GVector(int dimensity, const T &item) {
        sequence = new ArraySequence<T>(dimensity, item);
    }

    template<typename T>
    GVector<T>::GVector(int dimensity, const T *items) {
        sequence = new ArraySequence<T>(dimensity, items);
    }

    template<typename T>
    GVector<T>::GVector(const DynamicArray<T> &array) {
        sequence = new ArraySequence<T>(array);
    }

    template<typename T>
    GVector<T>::GVector(const LinkedList<T> &list) {
        sequence = new ArraySequence<T>(list);
    }

    template<typename T>
    GVector<T>::GVector(const Sequence<T> *sequence) {
        this->sequence = new ArraySequence<T>(sequence);
    }

    template<typename T>
    GVector<T>::GVector(const GVector<T> &other) {
        sequence = new ArraySequence<T>(other.sequence);
    }

    template<typename T>
    GVector<T>::~GVector() = default;

    template<typename T>
    GVector<T> &GVector<T>::operator=(const GVector<T> &other) {
        if (this != &other) {
            delete sequence;
            sequence = new ArraySequence<T>(other.sequence);
        }
        return *this;
    }

    template<typename T>
    T &GVector<T>::operator[](int index) {
        if (index < 0 || index >= dim())
            throw std::out_of_range("Index out of range!");

        return sequence->operator[](index);

    }

    template<typename T>
    T GVector<T>::Get(int index) const {
        return sequence->Get(index);
    }

    template<typename T>
    GVector<T> GVector<T>::operator+(const GVector<T>& other) {
        if (dim() != other.dim()) {
            throw std::invalid_argument("Different dim!");
        }
        GVector<T> result(dim());
        for (int i = 0; i < dim(); ++i) {
            result.sequence->Set(i, Get(i) + other.Get(i));
        }
        return result;
    }

    template<typename T>
    GVector<T> GVector<T>::operator-(const GVector<T>& other) {
        if (dim() != other.dim()) {
            throw std::invalid_argument("Different dim!");
        }
        GVector<T> result(dim());
        for (int i = 0; i < dim(); ++i) {
            result.sequence->Set(i, Get(i) - other.Get(i));
        }
        return result;
    }

    template<typename T>
    T GVector<T>::operator*(const GVector<T>& other) {
        if (dim() != other.dim()) {
            throw std::invalid_argument("Different dim!");
        }
        T result = T();
        for (int i = 0; i < dim(); ++i) {
            result += Get(i) * other.Get(i);
        }
        return result;
    }


    template<typename T>
    double GVector<T>::module() const {
        T result = T();
        for (int i = 0; i < dim(); ++i) {
            result += Get(i) * Get(i);
        }
        return sqrt(result);
    }

} // lab3

#endif //LAB3_GVECTOR_HPP
