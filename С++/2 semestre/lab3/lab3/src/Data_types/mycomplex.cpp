#include "mycomplex.h"
#include <cmath>

namespace lab3 {
    complex::complex() : re_(0), im_(0) {}
    complex::complex(double re) : re_(re), im_(0) {}
    complex::complex(double re, double im) : re_(re), im_(im) {}
    complex::complex(const complex &other) = default;
    complex::~complex() = default;
    complex &complex::operator=(const complex &other) = default;

    double complex::re() const {
        return re_;
    }
    double complex::im() const {
        return im_;
    }
    double complex::abs() const {
        return sqrt(re_ * re_ + im_ * im_);
    }
    double complex::arg() const {
        return atan2(im_, re_);
    }
    complex complex::conj() const {
        return {re_, -im_};
    }

    complex complex::operator+(const complex &other) const {
        return {re_ + other.re_, im_ + other.im_};
    }
    complex complex::operator-(const complex &other) const {
        return {re_ - other.re_, im_ - other.im_};
    }
    complex complex::operator*(const complex &other) const {
        return {re_ * other.re_ - im_ * other.im_, re_ * other.im_ + im_ * other.re_};
    }
    complex complex::operator/(const complex &other) const {
        double denominator = other.re_ * other.re_ + other.im_ * other.im_;
        return {(re_ * other.re_ + im_ * other.im_) / denominator,
                (im_ * other.re_ - re_ * other.im_) / denominator};
    }

    complex complex::operator+(double scalar) const {
        return {re_ + scalar, im_};
    }
    complex complex::operator-(double scalar) const {
        return {re_ - scalar, im_};
    }
    complex complex::operator*(double scalar) const {
        return {re_ * scalar, im_ * scalar};
    }
    complex complex::operator/(double scalar) const {
        return {re_ / scalar, im_ / scalar};
    }

    complex &complex::operator+=(const complex &other) {
        re_ += other.re_;
        im_ += other.im_;
        return *this;
    }
    complex &complex::operator-=(const complex &other) {
        re_ -= other.re_;
        im_ -= other.im_;
        return *this;
    }
    complex &complex::operator*=(const complex &other) {\
        double new_re = re_ * other.re_ - im_ * other.im_;
        double new_im = re_ * other.im_ + im_ * other.re_;

        re_ = new_re;
        im_ = new_im;

        return *this;
    }
    complex &complex::operator/=(const complex &other) {
        double denominator = other.re_ * other.re_ + other.im_ * other.im_;
        double new_re = (re_ * other.re_ + im_ * other.im_) / denominator;
        double new_im = (im_ * other.re_ - re_ * other.im_) / denominator;

        re_ = new_re;
        im_ = new_im;

        return *this;
    }

    complex &complex::operator+=(double scalar) {
        re_ += scalar;
        return *this;
    }
    complex &complex::operator-=(double scalar) {
        re_ -= scalar;
        return *this;
    }
    complex &complex::operator*=(double scalar) {
        re_ *= scalar;
        im_ *= scalar;
        return *this;
    }
    complex &complex::operator/=(double scalar) {
        re_ /= scalar;
        im_ /= scalar;
        return *this;
    }

    bool complex::operator==(const complex &other) const {
        return re_ == other.re_ && im_ == other.im_;
    }
    bool complex::operator!=(const complex &other) const {
        return re_ != other.re_ || im_ != other.im_;
    }
} // lab3