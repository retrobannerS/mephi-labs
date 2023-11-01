#ifndef LAB3_COMPLEX_H
#define LAB3_COMPLEX_H
#include <iostream>

using namespace std;

namespace lab3 {

    class complex {
    private:
        double re_;
        double im_;
    public:
        complex();
        explicit complex(double re);
        complex(double re, double im);
        complex(const complex &other);
        ~complex();

        complex &operator=(const complex &other);

        [[nodiscard]] double re() const;
        [[nodiscard]] double im() const;
        [[nodiscard]] double abs() const;
        [[nodiscard]] double arg() const;
        [[nodiscard]] complex conj() const;

        complex operator+(const complex &other) const;
        complex operator-(const complex &other) const;
        complex operator*(const complex &other) const;
        complex operator/(const complex &other) const;

        complex operator+(double scalar) const;
        complex operator-(double scalar) const;
        complex operator*(double scalar) const;
        complex operator/(double scalar) const;

        friend complex operator+(double scalar, const complex &other) {
            return other + scalar;
        }
        friend complex operator-(double scalar, const complex &other) {
            return {scalar - other.re(), -other.im()};
        }
        friend complex operator*(double scalar, const complex &other) {
            return other * scalar;
        }
        friend complex operator/(double scalar, const complex &other) {
            return complex(scalar, 0) / other;
        }

        complex &operator+=(const complex &other);
        complex &operator-=(const complex &other);
        complex &operator*=(const complex &other);
        complex &operator/=(const complex &other);

        complex &operator+=(double scalar);
        complex &operator-=(double scalar);
        complex &operator*=(double scalar);
        complex &operator/=(double scalar);

        bool operator==(const complex &other) const;
        bool operator!=(const complex &other) const;

        friend ostream &operator<<(ostream &out, const complex &other) {
            out << other.re() << " + " << other.im() << "i";
            return out;
        }
    };
} // lab3

#endif //LAB3_COMPLEX_H
