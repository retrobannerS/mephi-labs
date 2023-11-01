#ifndef LAB3_DIAGMATRIX_HPP
#define LAB3_DIAGMATRIX_HPP
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include <string>
#include <iomanip>

using namespace std;
using namespace lab2;

namespace lab3 {
    template<typename T>
    class DiagMatrix {
    private:
        int dimensity;
        Sequence<T> *data;
        [[nodiscard]] int getIndex(int i, int j) const;
    public:
        explicit DiagMatrix(int dimensity);
        DiagMatrix(int dimensity, const T &item);
        DiagMatrix(int dimensity, const T *items);
        explicit DiagMatrix(const Sequence<T> *sequence);
        DiagMatrix(const DiagMatrix<T> &other);
        ~DiagMatrix();

        DiagMatrix<T> &operator=(const DiagMatrix<T> &other);

        [[nodiscard]] int dim() const;

        T &operator()(int i, int j);
        T get(int i, int j) const;
        void set(int i, int j, const T &item);

        DiagMatrix<T> operator+(const DiagMatrix<T> &other);
        DiagMatrix<T> operator-(const DiagMatrix<T> &other);
        friend DiagMatrix<T> operator*(const T &scalar, const DiagMatrix<T> &matrix) {
            DiagMatrix<T> result(matrix.dim());
            for (int i = 0; i < matrix.dim(); ++i) {
                result.set(i, i, matrix.get(i, i) * scalar);
            }
            return result;
        }
        friend DiagMatrix<T> operator*(const DiagMatrix<T> &matrix, const T &scalar) {
            DiagMatrix<T> result(matrix.dim());
            for (int i = 0; i < matrix.dim(); ++i) {
                result.set(i, i, matrix.get(i, i) * scalar);
            }
            return result;
        }
        friend ostream &operator<<(ostream &out, const DiagMatrix<T> &matrix) {
            if(matrix.dim() == 0) {
                out << "Empty matrix" << std::endl;
                return out;
            }
            int max_length = 0;
            for (int i = 0; i < matrix.dim(); ++i) {
                int elem_length = std::to_string(matrix.get(i, i)).length();
                max_length = std::max(max_length, elem_length);
            }
            for (int i = 0; i < matrix.dim(); ++i) {
                out << "|";
                for (int j = 0; j < matrix.dim(); ++j) {
                    if(i == j) {
                        out << std::setw(max_length) << matrix.get(i, j);
                    } else {
                        out << std::setw(max_length) << T();
                    }
                }
                out << " |" << std::endl;
            }
            return out;
        }

        T trace() const;
        T det() const;
    };

    template<typename T>
    int DiagMatrix<T>::getIndex(int i, int j) const {
        if(i < 0 || i >= dimensity || j < 0 || j >= dimensity || i != j) {
            throw std::out_of_range("Index out of range!");
        }
        return i;
    }

    template<typename T>
    DiagMatrix<T>::DiagMatrix(int dimensity) {
        if(dimensity < 0) {
            throw std::invalid_argument("Invalid dimensity!");
        }
        this->dimensity = dimensity;
        this->data = new ArraySequence<T>(dimensity);
    }

    template<typename T>
    DiagMatrix<T>::DiagMatrix(int dimensity, const T &item) {
        if(dimensity < 0) {
            throw std::invalid_argument("Invalid dimensity!");
        }
        this->dimensity = dimensity;
        data = new ArraySequence<T>(dimensity, item);
    }

    template<typename T>
    DiagMatrix<T>::DiagMatrix(int dimensity, const T *items) {
        if(dimensity < 0) {
            throw std::invalid_argument("Invalid dimensity!");
        }
        this->dimensity = dimensity;
        data = new ArraySequence<T>(dimensity, items);
    }

    template<typename T>
    DiagMatrix<T>::DiagMatrix(const Sequence<T> *sequence) : data(new ArraySequence<T>(sequence)), dimensity(sequence->GetSize()) {}

    template<typename T>
    DiagMatrix<T>::DiagMatrix(const DiagMatrix<T> &other) {
        this->dimensity = other.dimensity;
        this->data = new ArraySequence<T>(other.data);
    }

    template<typename T>
    DiagMatrix<T>::~DiagMatrix() {
        delete data;
    }

    template<typename T>
    DiagMatrix<T> &DiagMatrix<T>::operator=(const DiagMatrix<T> &other) {
        if(this != &other) {
            delete data;
            this->dimensity = other.dimensity;
            this->data = new ArraySequence<T>(other.data);
        }
        return *this;
    }

    template<typename T>
    int DiagMatrix<T>::dim() const {
        return dimensity;
    }

    template<typename T>
    T &DiagMatrix<T>::operator()(int i, int j) {
        if(i < 0 || i >= dimensity || j < 0 || j >= dimensity) {
            throw std::out_of_range("Index out of range!");
        }
        return data->operator[](getIndex(i, j));
    }

    template<typename T>
    T DiagMatrix<T>::get(int i, int j) const {
        if(i < 0 || i >= dimensity || j < 0 || j >= dimensity) {
            throw std::out_of_range("Index out of range!");
        }
        return data->Get(getIndex(i, j));
    }

    template<typename T>
    void DiagMatrix<T>::set(int i, int j, const T &item) {
        if(i < 0 || i >= dimensity || j < 0 || j >= dimensity) {
            throw std::out_of_range("Index out of range!");
        }
        data->Set(getIndex(i, j), item);
    }

    template<typename T>
    DiagMatrix<T> DiagMatrix<T>::operator+(const DiagMatrix<T> &other) {
        if(dimensity != other.dimensity) {
            throw std::invalid_argument("Matrices have different dimensities!");
        }
        DiagMatrix<T> result(dimensity);
        for (int i = 0; i < dimensity; ++i) {
            result.set(i, i, this->get(i, i) + other.get(i, i));
        }
        return result;
    }

    template<typename T>
    DiagMatrix<T> DiagMatrix<T>::operator-(const DiagMatrix<T> &other) {
        if(dimensity != other.dimensity) {
            throw std::invalid_argument("Matrices have different dimensities!");
        }
        DiagMatrix<T> result(dimensity);
        for (int i = 0; i < dimensity; ++i) {
            result.set(i, i, this->get(i, i) - other.get(i, i));
        }
        return result;
    }

    template<typename T>
    T DiagMatrix<T>::trace() const {
        if(dimensity == 0) {
            throw std::logic_error("Empty matrix!");
        }
        T result = T();
        for (int i = 0; i < dimensity; ++i) {
            result += get(i, i);
        }
        return result;
    }

    template<typename T>
    T DiagMatrix<T>::det() const {
        if(dimensity == 0) {
            throw std::logic_error("Empty matrix!");
        }
        T result = T(1);
        for (int i = 0; i < dimensity; ++i) {
            result *= this->get(i, i);
        }
        return result;
    }
} // lab3

#endif //LAB3_DIAGMATRIX_HPP
