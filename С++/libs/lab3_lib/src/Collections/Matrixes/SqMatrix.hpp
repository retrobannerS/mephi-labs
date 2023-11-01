#ifndef LAB3_SQMATRIX_HPP
#define LAB3_SQMATRIX_HPP
#include <stdexcept>
#include <iomanip>
#include <string>
#include "Sequence.hpp"
#include "ArraySequence.hpp"

using namespace lab2;

namespace lab3 {
    template<typename T>
    class SqMatrix {
    private:
        int dimensity{};
        Sequence<T> *data;
        T zero = T();
        T one = T(1);
        T minusOne = T(-1);
        T getMinor(int row, int col) const;
        T algCompl(int row, int col) const;
    public:
        explicit SqMatrix(int dimensity);
        SqMatrix(int dimensity, const T &item);
        SqMatrix(const SqMatrix<T> &another);
        ~SqMatrix();

        void setRing(T zero, T one_item, T minusOne_item);
        void makeZero();
        void makeOne();
        void makeDiag(const T &item);

        [[nodiscard]] int dim() const;
        T get(int row, int col) const;
        Sequence<T> *getRow(int row) const;
        Sequence<T> *getCol(int col) const;

        void set(int row, int col, const T &item);
        void setRow(int row, const Sequence<T> &sq);
        void setCol(int col, const Sequence<T> &sq);
        //[i][j] == (i, j)
        T &operator()(int row, int col);
        SqMatrix<T> operator +(const SqMatrix<T> &another) const;
        SqMatrix<T> operator -(const SqMatrix<T> &another) const;
        SqMatrix<T> operator *(const SqMatrix<T> &another) const;
        friend SqMatrix<T> operator *(const T &scalar, const SqMatrix<T> &matrix) {
            SqMatrix<T> result(matrix.dim());
            for (int i = 0; i < matrix.dim(); ++i) {
                for (int j = 0; j < matrix.dim(); ++j) {
                    result.set(i, j, matrix.get(i, j) * scalar);
                }
            }
            return result;
        }
        friend SqMatrix<T> operator *(const SqMatrix<T> &matrix, const T &scalar) {
            SqMatrix<T> result(matrix.dim());
            for (int i = 0; i < matrix.dim(); ++i) {
                for (int j = 0; j < matrix.dim(); ++j) {
                    result.set(i, j, matrix.get(i, j) * scalar);
                }
            }
            return result;
        }
        SqMatrix<T> &operator =(const SqMatrix<T> &another);
        friend std::ostream &operator <<(std::ostream &out, const SqMatrix<T> &matrix) {
            if(matrix.dim() == 0) {
                out << "Empty matrix" << std::endl;
                return out;
            }
            int max_length = 0;
            for (int i = 0; i < matrix.dim(); ++i) {
                for (int j = 0; j < matrix.dim(); ++j) {
                    int element_length = std::to_string(matrix.get(i, j)).length();
                    max_length = std::max(max_length, element_length);
                }
            }
            for (int i = 0; i < matrix.dim(); ++i) {
                out << "| ";
                for (int j = 0; j < matrix.dim(); ++j) {
                    out << std::setw(max_length) << matrix.get(i, j) << " ";
                }
                out << "|" << std::endl;
            }
            return out;
        }

        T det() const;
        T trace() const;
        SqMatrix<T> transpose();
        SqMatrix<T> inverse();
    };

    template<typename T>
    T SqMatrix<T>::getMinor(int row, int col) const {
        SqMatrix<T> minor(dim() - 1);
        for (int i = 0; i < dim(); ++i) {
            for (int j = 0; j < dim(); ++j) {
                if(i == row || j == col) {
                    continue;
                }
                minor.set(i < row ? i : i - 1, j < col ? j : j - 1, get(i, j));
            }
        }
        return minor.det();
    }

    template<typename T>
    T SqMatrix<T>::algCompl(int row, int col) const {
        return ((row + col) % 2 == 0 ? one : minusOne) * getMinor(row, col);
    }

    template<typename T>
    SqMatrix<T>::SqMatrix(int dimensity) {
        if(dimensity < 0) {
            throw std::invalid_argument("Dimensity must be positive!");
        }
        this->dimensity = dimensity;
        data = new ArraySequence<T>(dimensity * dimensity);
    }

    template<typename T>
    SqMatrix<T>::SqMatrix(int dimensity, const T &item) {
        if(dimensity < 0) {
            throw std::invalid_argument("Dimensity must be positive!");
        }
        this->dimensity = dimensity;
        data = new ArraySequence<T>(dimensity * dimensity, item);
    }

    template<typename T>
    SqMatrix<T>::SqMatrix(const SqMatrix<T> &another) {
        dimensity = another.dimensity;
        data = new ArraySequence<T>(another.data);
        one = another.one;
        minusOne = another.minusOne;
        zero = another.zero;
    }

    template<typename T>
    SqMatrix<T>::~SqMatrix() {
        delete data;
    }

    template<typename T>
    void SqMatrix<T>::setRing(T zero_item, T one_item, T minusOne_item) {
        this->zero = zero_item;
        this->one = one_item;
        this->minusOne = minusOne_item;
    }

    template<typename T>
    void SqMatrix<T>::makeZero() {
        for (int i = 0; i < dimensity * dimensity; ++i) {
            data->Set(i, T());
        }
    }

    template<typename T>
    void SqMatrix<T>::makeOne() {
        makeDiag(one);
    }

    template<typename T>
    void SqMatrix<T>::makeDiag(const T &item) {
        makeZero();
        for (int i = 0; i < dimensity; ++i) {
            data->Set(i * dimensity + i, item);
        }
    }

    template<typename T>
    int SqMatrix<T>::dim() const {
        return dimensity;
    }

    template<typename T>
    T SqMatrix<T>::get(int row, int col) const {
        if(row < 0 || row >= dimensity || col < 0 || col >= dimensity) {
            throw std::out_of_range("Index out of range!");
        }
        return data->Get(row * dimensity + col);
    }

    template<typename T>
    Sequence<T> *SqMatrix<T>::getRow(int row) const {
        if(row < 0 || row >= dimensity) {
            throw std::out_of_range("Index out of range!");
        }
        Sequence<T> *result = new ArraySequence<T>(dimensity);
        for (int i = 0; i < dimensity; ++i) {
            result->Set(i, data->Get(row * dimensity + i));
        }
        return result;
    }

    template<typename T>
    Sequence<T> *SqMatrix<T>::getCol(int col) const {
        if(col < 0 || col >= dimensity) {
            throw std::out_of_range("Index out of range!");
        }
        Sequence<T> *result = new ArraySequence<T>(dimensity);
        for (int i = 0; i < dimensity; ++i) {
            result->Set(i, data->Get(i * dimensity + col));
        }
        return result;
    }

    template<typename T>
    void SqMatrix<T>::set(int row, int col, const T &item) {
        if(row < 0 || row >= dimensity || col < 0 || col >= dimensity) {
            throw std::out_of_range("Index out of range!");
        }
        data->Set(row * dimensity + col, item);
    }

    template<typename T>
    void SqMatrix<T>::setRow(int row, const Sequence<T> &sq) {
        if(row < 0 || row >= dimensity) {
            throw std::out_of_range("Index out of range!");
        }
        if(sq.GetSize() != dimensity) {
            throw std::invalid_argument("Invalid sequence size!");
        }
        for (int i = 0; i < dimensity; ++i) {
            data->Set(row * dimensity + i, sq.Get(i));
        }
    }

    template<typename T>
    void SqMatrix<T>::setCol(int col, const Sequence<T> &sq) {
        if(col < 0 || col >= dimensity) {
            throw std::out_of_range("Index out of range!");
        }
        if(sq.GetSize() != dimensity) {
            throw std::invalid_argument("Invalid sequence size!");
        }
        for (int i = 0; i < dimensity; ++i) {
            data->Set(i * dimensity + col, sq.Get(i));
        }
    }

    template<typename T>
    T &SqMatrix<T>::operator()(int row, int col) {
        if(row < 0 || row >= dimensity || col < 0 || col >= dimensity) {
            throw std::out_of_range("Index out of range!");
        }
        return data->operator[](row * dimensity + col);
    }

    template<typename T>
    SqMatrix<T> SqMatrix<T>::operator +(const SqMatrix<T> &another) const {
        if(dimensity != another.dim()) {
            throw std::invalid_argument("Invalid dimensities!");
        }
        SqMatrix<T> result(dimensity);
        for (int i = 0; i < dimensity * dimensity; ++i) {
            result.data->Set(i, data->Get(i) + another.data->Get(i));
        }
        return result;
    }

    template<typename T>
    SqMatrix<T> SqMatrix<T>::operator -(const SqMatrix<T> &another) const {
        if(dimensity != another.dim()) {
            throw std::invalid_argument("Invalid dimensities!");
        }
        SqMatrix<T> result(dimensity);
        for (int i = 0; i < dimensity * dimensity; ++i) {
            result.data->Set(i, data->Get(i) - another.data->Get(i));
        }
        return result;
    }

    template<typename T>
    SqMatrix<T> SqMatrix<T>::operator *(const SqMatrix<T> &another) const {
        if(dimensity != another.dim()) {
            throw std::invalid_argument("Invalid dimensities!");
        }
        SqMatrix<T> result(dimensity);
        for (int i = 0; i < dimensity; ++i) {
            for (int j = 0; j < dimensity; ++j) {
                T sum = T();
                for (int k = 0; k < dimensity; ++k) {
                    sum += get(i, k) * another.get(k, j);
                }
                result.set(i, j, sum);
            }
        }
        return result;
    }

    template<typename T>
    SqMatrix<T> &SqMatrix<T>::operator =(const SqMatrix<T> &another) {
        if(this != &another) {
            delete data;
            dimensity = another.dim();
            data = new ArraySequence<T>(dimensity * dimensity);
            for (int i = 0; i < dimensity * dimensity; ++i) {
                data->Set(i, another.data->Get(i));
            }
            one = another.one;
            minusOne = another.minusOne;
            zero = another.zero;
        }
        return *this;
    }

    template<typename T>
    T SqMatrix<T>::det() const {
        if(dimensity == 1) {
            return get(0, 0);
        }
        T result = T();
        for (int i = 0; i < dimensity; ++i) {
            result += algCompl(0, i) * get(0, i);
        }
        return result;
    }

    template<typename T>
    T SqMatrix<T>::trace() const {
        T result = T();
        for (int i = 0; i < dimensity; ++i) {
            result += get(i, i);
        }
        return result;
    }

    template<typename T>
    SqMatrix<T> SqMatrix<T>::transpose() {
        SqMatrix<T> result(dimensity);
        for (int i = 0; i < dimensity; ++i) {
            for (int j = 0; j < dimensity; ++j) {
                result.set(i, j, get(j, i));
            }
        }
        return result;
    }

    template<typename T>
    SqMatrix<T> SqMatrix<T>::inverse() {
        SqMatrix<T> result(dimensity);
        T det = this->det();
        if(det == zero) {
            throw std::invalid_argument("Determinant is zero!");
        }
        for (int i = 0; i < dimensity; ++i) {
            for (int j = 0; j < dimensity; ++j) {
                result.set(i, j, algCompl(j, i) / det);
            }
        }
        return result;
    }

} // lab3

#endif //LAB3_SQMATRIX_HPP
