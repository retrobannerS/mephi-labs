#ifndef LAB2CORRECT2_OPTIONS_HPP
#define LAB2CORRECT2_OPTIONS_HPP

namespace lab2 {
    template <typename T>
    class Options {
    private:
        T value_ = T();
        bool has_value_ = false;
    public:
        Options();
        Options(const T &value);
        Options(const Options<T> &another);
        ~Options();
        bool HasValue() const;
        T Value() const;
        T ValueOr(const T &default_value) const;
    };

} // lab2

#include "Options.cpp"
#endif //LAB2CORRECT2_OPTIONS_HPP
