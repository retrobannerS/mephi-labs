#ifndef LAB3_TRIANGULARMATRIX_HPP
#define LAB3_TRIANGULARMATRIX_HPP

#include <string>
#include <iomanip>
#include "Sequence.hpp"
#include "ArraySequence.hpp"

using namespace lab2;

namespace lab3 {

    template<typename T>
    class LowerTriangularMatrix;

    template<typename T>
    class UpperTriangularMatrix;

    template<typename T>
    class TriangularMatrix {
    protected:
        Sequence<T> *data;
        int dimensity = 0;
        [[nodiscard]] virtual int getIndex(int row, int col) const = 0;
    public:
        virtual ~TriangularMatrix();
        [[nodiscard]] int dim() const;

        virtual T &operator()(int row, int col);
        T get(int row, int col) const;
        void set(int row, int col, const T &item);

        friend std::ostream &operator<<(std::ostream &out, const TriangularMatrix<T> &matrix) {
            if(matrix.dim() == 0) {
                out << "Empty matrix" << std::endl;
                return out;
            }
            int max_length = 0;
            for (int i = 0; i < matrix.dim(); ++i) {
                for (int j = 0; j < matrix.dim(); ++j) {
                    try {
                        int element_length = std::to_string(matrix.get(i, j)).length();
                        max_length = std::max(max_length, element_length);
                    } catch (std::out_of_range &e) {
                        int element_length = std::to_string(T(0)).length();
                        max_length = std::max(max_length, element_length);
                    }
                }
            }
            for (int i = 0; i < matrix.dim(); ++i) {
                out << "|";
                for (int j = 0; j < matrix.dim(); ++j) {
                    try {
                        out << std::setw(max_length) << matrix.get(i, j);
                    } catch (std::out_of_range &e) {
                        out << std::setw(max_length) << T();
                    }
                }
                out << " |" << std::endl;
            }
            return out;
        }

        T trace();
        T det();
    };

    template<typename T>
    class LowerTriangularMatrix : public TriangularMatrix<T>{
    private:
        using TriangularMatrix<T>::data;
        using TriangularMatrix<T>::dimensity;
        [[nodiscard]] int getIndex(int row, int col) const override;
    public:
        explicit LowerTriangularMatrix(int dimensity);
        LowerTriangularMatrix(int dimensity, const T &item);
        LowerTriangularMatrix(const LowerTriangularMatrix<T> &other);
        ~LowerTriangularMatrix();

        LowerTriangularMatrix<T> &operator=(const LowerTriangularMatrix<T> &other);
        LowerTriangularMatrix<T> operator+(const LowerTriangularMatrix<T> &other);
        LowerTriangularMatrix<T> operator-(const LowerTriangularMatrix<T> &other);
        friend LowerTriangularMatrix<T> operator*(const LowerTriangularMatrix<T> &matrix, const T &scalar) {
            LowerTriangularMatrix<T> result(matrix.dim());
            for (int i = 0; i < matrix.dim(); ++i) {
                for (int j = 0; j < matrix.dim(); ++j) {
                    result.Set(i, j, matrix.Get(i, j) * scalar);
                }
            }
            return result;
        }
        friend LowerTriangularMatrix<T> operator*(const T &scalar, const LowerTriangularMatrix<T> &matrix) {
            return matrix * scalar;
        }

        UpperTriangularMatrix <T> *transpose();
    };

    template<typename T>
    class UpperTriangularMatrix : public TriangularMatrix<T>{
    private:
        using TriangularMatrix<T>::data;
        using TriangularMatrix<T>::dimensity;
        [[nodiscard]] int getIndex(int row, int col) const override;
    public:
        explicit UpperTriangularMatrix(int dimensity);
        UpperTriangularMatrix(int dimensity, const T &item);
        UpperTriangularMatrix(const UpperTriangularMatrix<T> &other);
        ~UpperTriangularMatrix();

        UpperTriangularMatrix<T> &operator=(const UpperTriangularMatrix<T> &other);
        UpperTriangularMatrix<T> operator+(const UpperTriangularMatrix<T> &other);
        UpperTriangularMatrix<T> operator-(const UpperTriangularMatrix<T> &other);
        friend UpperTriangularMatrix<T> operator*(const UpperTriangularMatrix<T> &matrix, const T &scalar) {
            UpperTriangularMatrix<T> result(matrix.dim());
            for (int i = 0; i < matrix.dim(); ++i) {
                for (int j = 0; j < matrix.dim(); ++j) {
                    result.Set(i, j, matrix.Get(i, j) * scalar);
                }
            }
            return result;
        }
        friend UpperTriangularMatrix<T> operator*(const T &scalar, const UpperTriangularMatrix<T> &matrix) {
            return matrix * scalar;
        }

        LowerTriangularMatrix <T> *transpose();
    };

    template<typename T>
    TriangularMatrix<T>::~TriangularMatrix() = default;

    template<typename T>
    int TriangularMatrix<T>::dim() const {
        return dimensity;
    }

    template<typename T>
    T &TriangularMatrix<T>::operator()(int row, int col) {
        if(row < 0 || col < 0 || row >= dimensity || col >= dimensity) {
            throw std::out_of_range("Index out of range");
        }
        return data->operator[](getIndex(row, col));
    }

    template<typename T>
    T TriangularMatrix<T>::get(int row, int col) const {
        if(row < 0 || col < 0 || row >= dimensity || col >= dimensity) {
            throw std::out_of_range("Index out of range");
        }
        return data->Get(getIndex(row, col));
    }

    template<typename T>
    void TriangularMatrix<T>::set(int row, int col, const T &item) {
        if(row < 0 || col < 0 || row >= dimensity || col >= dimensity) {
            throw std::out_of_range("Index out of range");
        }
        data->Set(getIndex(row, col), item);
    }

    template<typename T>
    T TriangularMatrix<T>::trace() {
        T result = T();
        for (int i = 0; i < dimensity; ++i) {
            result += get(i, i);
        }
        return result;
    }

    template<typename T>
    T TriangularMatrix<T>::det() {
        T result = T(1);
        for(int i = 0; i != dimensity; ++i) {
            for(int j = 0; j != dimensity; ++j) {
                if(i == j) {
                    result *= get(i, j);
                }
            }
        }
        return result;
    }

    template<typename T>
    int LowerTriangularMatrix<T>::getIndex(int row, int col) const {
        if(row < col) {
            throw std::out_of_range("Index out of range");
        }
        return row * (row + 1) / 2 + col;
    }

    template<typename T>
    LowerTriangularMatrix<T>::LowerTriangularMatrix(int dimensity) {
        if(dimensity < 0) {
            throw std::invalid_argument("Invalid dimensity");
        }
        this->dimensity = dimensity;
        data = new ArraySequence<T>(dimensity * (dimensity + 1) / 2);
    }

    template<typename T>
    LowerTriangularMatrix<T>::LowerTriangularMatrix(int dimensity, const T &item) {
        if(dimensity < 0) {
            throw std::invalid_argument("Invalid dimensity!");
        }
        this->dimensity = dimensity;
        data = new ArraySequence<T>(dimensity * (dimensity + 1) / 2, item);
    }

    template<typename T>
    LowerTriangularMatrix<T>::LowerTriangularMatrix(const LowerTriangularMatrix<T> &other) {
        dimensity = other.dimensity;
        data = new ArraySequence<T>(other.data);
    }

    template<typename T>
    LowerTriangularMatrix<T>::~LowerTriangularMatrix() {
        delete data;
    }

    template<typename T>
    LowerTriangularMatrix<T> &LowerTriangularMatrix<T>::operator=(const LowerTriangularMatrix<T> &other) {
        if(this != &other) {
            dimensity = other.dimensity;
            delete data;
            data = new ArraySequence<T>(other.data);
        }
        return *this;
    }

    template<typename T>
    LowerTriangularMatrix<T> LowerTriangularMatrix<T>::operator+(const LowerTriangularMatrix<T> &other) {
        if(dimensity != other.dimensity) {
            throw std::invalid_argument("Matrices have different dimensity");
        }
        LowerTriangularMatrix<T> result(dimensity);
        for (int i = 0; i < dimensity; ++i) {
            for (int j = i; j < dimensity; ++j) {
                result(j, i) = this->get(j, i) + other.get(j, i);
            }
        }
        return result;
    }


    template<typename T>
    LowerTriangularMatrix<T> LowerTriangularMatrix<T>::operator-(const LowerTriangularMatrix<T> &other) {
        if(dimensity != other.dimensity) {
            throw std::invalid_argument("Matrices have different dimensity");
        }
        LowerTriangularMatrix<T> result(dimensity);
        for (int i = 0; i < dimensity; ++i) {
            for (int j = i; j < dimensity; ++j) {
                result(j, i) = this->get(j, i) - other.get(j, i);
            }
        }
        return result;
    }

    template<typename T>
    UpperTriangularMatrix<T> *LowerTriangularMatrix<T>::transpose() {
        auto *result = new UpperTriangularMatrix<T>(dimensity);
        for (int i = 0; i < dimensity; ++i) {
            for (int j = i; j < dimensity; ++j) {
                result->set(i, j, this->get(j, i));
            }
        }
        return result;
    }

    template<typename T>
    int UpperTriangularMatrix<T>::getIndex(int row, int col) const {
        if(row > col) {
            throw std::out_of_range("Index out of range");
        }
        return row * (row + 1) / 2 + col;
    }

    template<typename T>
    UpperTriangularMatrix<T>::UpperTriangularMatrix(int dimensity) {
        if(dimensity < 0) {
            throw std::invalid_argument("Invalid dimensity");
        }
        this->dimensity = dimensity;
        data = new ArraySequence<T>(dimensity * (dimensity + 1) / 2);
    }

    template<typename T>
    UpperTriangularMatrix<T>::UpperTriangularMatrix(int dimensity, const T &item) {
        if(dimensity < 0) {
            throw std::invalid_argument("Invalid dimensity!");
        }
        this->dimensity = dimensity;
        data = new ArraySequence<T>(dimensity * (dimensity + 1) / 2, item);
    }

    template<typename T>
    UpperTriangularMatrix<T>::UpperTriangularMatrix(const UpperTriangularMatrix<T> &other) {
        dimensity = other.dimensity;
        data = new ArraySequence<T>(other.data);
    }

    template<typename T>
    UpperTriangularMatrix<T>::~UpperTriangularMatrix() {
        delete data;
    }

    template<typename T>
    UpperTriangularMatrix<T> &UpperTriangularMatrix<T>::operator=(const UpperTriangularMatrix<T> &other) {
        if(this != &other) {
            dimensity = other.dimensity;
            delete data;
            data = new ArraySequence<T>(other.data);
        }
        return *this;
    }

    template<typename T>
    UpperTriangularMatrix<T> UpperTriangularMatrix<T>::operator+(const UpperTriangularMatrix<T> &other) {
        if(dimensity != other.dimensity) {
            throw std::invalid_argument("Matrices have different dimensity");
        }
        UpperTriangularMatrix<T> result(dimensity);
        for (int i = 0; i < dimensity; ++i) {
            for (int j = i; j < dimensity; ++j) {
                result(i, j) = this->get(i, j) + other.get(i, j);
            }
        }
        return result;
    }

    template<typename T>
    UpperTriangularMatrix<T> UpperTriangularMatrix<T>::operator-(const UpperTriangularMatrix<T> &other) {
        if(dimensity != other.dimensity) {
            throw std::invalid_argument("Matrices have different dimensity");
        }
        UpperTriangularMatrix<T> result(dimensity);
        for (int i = 0; i < dimensity; ++i) {
            for (int j = i; j < dimensity; ++j) {
                result(i, j) = this->get(i, j) - other.get(i, j);
            }
        }
        return result;
    }

    template<typename T>
    LowerTriangularMatrix<T> *UpperTriangularMatrix<T>::transpose() {
        auto *result = new LowerTriangularMatrix<T>(dimensity);
        for (int i = 0; i < dimensity; ++i) {
            for (int j = i; j < dimensity; ++j) {
                result->set(j, i, this->get(i, j));
            }
        }
        return result;
    }
} // lab3

#endif //LAB3_TRIANGULARMATRIX_HPP
