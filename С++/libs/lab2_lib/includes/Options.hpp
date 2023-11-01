#ifndef LAB2CORRECT2_OPTIONS_HPP
#define LAB2CORRECT2_OPTIONS_HPP
#include <stdexcept>

namespace lab2 {
    template <typename T>
    class Options {
    private:
        T value_ = T();
        bool has_value_ = false;
    public:
        Options() = default;
        explicit Options(const T &value);
        Options(const Options<T> &another);
        ~Options();
        [[nodiscard]] bool HasValue() const;
        T Value() const;
        T ValueOr(const T &default_value) const;
    };

    template <typename T>
    Options<T>::Options(const T &value) {
        this->value_ = value;
        this->has_value_ = true;
    }

    template <typename T>
    Options<T>::Options(const Options<T> &another) {
        this->value_ = another.value_;
        this->has_value_ = another.has_value_;
    }

    template <typename T>
    Options<T>::~Options() = default;

    template <typename T>
    [[maybe_unused]] bool Options<T>::HasValue() const {
        return this->has_value_;
    }

    template <typename T>
    T Options<T>::Value() const {
        if(!this->has_value_) {
            throw std::logic_error("No value!");
        }
        return this->value_;
    }

    template <typename T>
    T Options<T>::ValueOr(const T &default_value) const {
        if(!this->has_value_) {
            return default_value;
        }
        return this->value_;
    }
} // lab2

#endif //LAB2CORRECT2_OPTIONS_HPP
