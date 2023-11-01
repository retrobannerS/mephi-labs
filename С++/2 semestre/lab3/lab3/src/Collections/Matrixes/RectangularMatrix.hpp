#ifndef LAB3_RECTANGULARMATRIX_HPP
#define LAB3_RECTANGULARMATRIX_HPP
#include <utility>
#include <string>
#include <iomanip>
#include "Sequence.hpp"
#include "ArraySequence.hpp"

using namespace std;
using namespace lab2;

namespace lab3 {

    template<typename T>
    class RectangularMatrix {
    private:
        int _rows;
        int _cols;
        Sequence<T> *data;
        [[nodiscard]] int getIndex(int i, int j) const;
    public:
        RectangularMatrix(int rows, int cols);
        RectangularMatrix(int rows, int cols, const T &item);
        RectangularMatrix(const RectangularMatrix<T> &other);
        ~RectangularMatrix();

        RectangularMatrix<T> &operator=(const RectangularMatrix<T> &other);

        [[nodiscard]] int rows() const;
        [[nodiscard]] int cols() const;
        [[nodiscard]] pair<int, int> shape() const;

        T &operator()(int i, int j);
        T get(int i, int j) const;
        void set(int i, int j, const T &item);
        void setRow(int i, const Sequence<T> &row);
        void setCol(int j, const Sequence<T> &col);

        RectangularMatrix<T> operator+(const RectangularMatrix<T> &other) const;
        RectangularMatrix<T> operator-(const RectangularMatrix<T> &other) const;
        RectangularMatrix<T> operator*(const RectangularMatrix<T> &other) const;
        friend RectangularMatrix<T> operator*(const T &scalar, const RectangularMatrix<T> &matrix) {
            RectangularMatrix<T> result(matrix.rows(), matrix.cols());
            for (int i = 0; i < matrix.rows(); ++i) {
                for (int j = 0; j < matrix.cols(); ++j) {
                    result.set(i, j, matrix.get(i, j) * scalar);
                }
            }
            return result;
        }
        friend RectangularMatrix<T> operator*(const RectangularMatrix<T> &matrix, const T &scalar) {
            RectangularMatrix<T> result(matrix.rows(), matrix.cols());
            for (int i = 0; i < matrix.rows(); ++i) {
                for (int j = 0; j < matrix.cols(); ++j) {
                    result.set(i, j, matrix.get(i, j) * scalar);
                }
            }
            return result;
        }
        friend ostream &operator<<(ostream &out, const RectangularMatrix<T> &matrix) {
            if(matrix.rows() == 0 || matrix.cols() == 0) {
                out << "Empty matrix" << std::endl;
                return out;
            }
            int max_length = 0;
            for (int i = 0; i < matrix.rows(); ++i) {
                for (int j = 0; j < matrix.cols(); ++j) {
                    int elem_length = std::to_string(matrix.get(i, j)).length();
                    max_length = std::max(max_length, elem_length);
                }
            }
            for (int i = 0; i < matrix.rows(); ++i) {
                out << "|";
                for (int j = 0; j < matrix.cols(); ++j) {
                    out << std::setw(max_length) << matrix.get(i, j);
                }
                out << " |" << std::endl;
            }
            return out;
        }
        RectangularMatrix<T> transpose() const;
        RectangularMatrix<T> submatrix(int i, int j) const;
    };

    template<typename T>
    int RectangularMatrix<T>::getIndex(int i, int j) const {
        if(i < 0 || i >= _rows || j < 0 || j >= _cols) {
            throw std::out_of_range("Index out of range!");
        }
        return i * _cols + j;
    }

    template<typename T>
    RectangularMatrix<T>::RectangularMatrix(int rows, int cols) {
        if(rows < 0 || cols < 0 || rows == 0 && cols != 0 || cols == 0 && rows != 0) {
            throw std::invalid_argument("Invalid shape!");
        }
        _rows = rows;
        _cols = cols;
        data = new ArraySequence<T>(rows * cols);
    }

    template<typename T>
    RectangularMatrix<T>::RectangularMatrix(int rows, int cols, const T &item) {
        if(rows < 0 || cols < 0 || rows == 0 && cols != 0 || cols == 0 && rows != 0) {
            throw std::invalid_argument("Invalid shape!");
        }
        _rows = rows;
        _cols = cols;
        data = new ArraySequence<T>(rows * cols, item);
    }

    template<typename T>
    RectangularMatrix<T>::RectangularMatrix(const RectangularMatrix<T> &other) {
        _rows = other._rows;
        _cols = other._cols;
        data = new ArraySequence<T>(other.data);
    }

    template<typename T>
    RectangularMatrix<T>::~RectangularMatrix() {
        delete data;
    }

    template<typename T>
    RectangularMatrix<T> &RectangularMatrix<T>::operator=(const RectangularMatrix<T> &other) {
        if(this != &other) {
            _rows = other._rows;
            _cols = other._cols;
            delete data;
            data = new ArraySequence<T>(other.data);
        }
        return *this;
    }

    template<typename T>
    int RectangularMatrix<T>::rows() const {
        return _rows;
    }

    template<typename T>
    int RectangularMatrix<T>::cols() const {
        return _cols;
    }

    template<typename T>
    pair<int, int> RectangularMatrix<T>::shape() const {
        return {_rows, _cols};
    }

    template<typename T>
    T &RectangularMatrix<T>::operator()(int i, int j) {
        return data->operator[](getIndex(i, j));
    }

    template<typename T>
    T RectangularMatrix<T>::get(int i, int j) const {
        return data->Get(getIndex(i, j));
    }

    template<typename T>
    void RectangularMatrix<T>::set(int i, int j, const T &item) {
        return data->Set(getIndex(i, j), item);
    }

    template<typename T>
    void RectangularMatrix<T>::setRow(int i, const Sequence<T> &row) {
        if(row.GetSize() != _cols) {
            throw std::invalid_argument("Invalid size of sequence!");
        }
        for (int j = 0; j < _cols; ++j) {
            set(i, j, row.Get(j));
        }
    }

    template<typename T>
    void RectangularMatrix<T>::setCol(int j, const Sequence<T> &col) {
        if(col.GetSize() != _rows) {
            throw std::invalid_argument("Invalid size of sequence!");
        }
        for (int i = 0; i < _rows; ++i) {
            set(i, j, col.Get(i));
        }
    }

    template<typename T>
    RectangularMatrix<T> RectangularMatrix<T>::operator+(const RectangularMatrix<T> &other) const {
        if(_rows != other._rows || _cols != other._cols) {
            throw std::invalid_argument("Invalid matrix sizes!");
        }
        RectangularMatrix<T> result(_rows, _cols);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                result.set(i, j, get(i, j) + other.get(i, j));
            }
        }
        return result;
    }

    template<typename T>
    RectangularMatrix<T> RectangularMatrix<T>::operator-(const RectangularMatrix<T> &other) const {
        if(_rows != other._rows || _cols != other._cols) {
            throw std::invalid_argument("Invalid matrix sizes!");
        }
        RectangularMatrix<T> result(_rows, _cols);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                result.set(i, j, get(i, j) - other.get(i, j));
            }
        }
        return result;
    }

    template<typename T>
    RectangularMatrix<T> RectangularMatrix<T>::operator*(const RectangularMatrix<T> &other) const {
        if(_cols != other._rows) {
            throw std::invalid_argument("Invalid matrix sizes!");
        }
        RectangularMatrix<T> result(_rows, other._cols);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < other._cols; ++j) {
                T sum = T();
                for (int k = 0; k < _cols; ++k) {
                    sum += get(i, k) * other.get(k, j);
                }
                result.set(i, j, sum);
            }
        }
        return result;
    }

    template<typename T>
    RectangularMatrix<T> RectangularMatrix<T>::transpose() const {
        RectangularMatrix<T> result(_cols, _rows);
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                result.set(j, i, get(i, j));
            }
        }
        return result;
    }

    template<typename T>
    RectangularMatrix<T> RectangularMatrix<T>::submatrix(int i, int j) const {
        RectangularMatrix<T> result(_rows - 1, _cols - 1);
        for (int k = 0; k < _rows; ++k) {
            for (int l = 0; l < _cols; ++l) {
                if(k < i && l < j) {
                    result.set(k, l, get(k, l));
                } else if(k < i && l > j) {
                    result.set(k, l - 1, get(k, l));
                } else if(k > i && l < j) {
                    result.set(k - 1, l, get(k, l));
                } else if(k > i && l > j) {
                    result.set(k - 1, l - 1, get(k, l));
                }
            }
        }
        return result;
    }

} // lab3

#endif //LAB3_RECTANGULARMATRIX_HPP
