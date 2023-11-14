#ifndef LAB1_UNIQUE_PTR_HPP
#define LAB1_UNIQUE_PTR_HPP
#include <utility>

namespace sem3 {

    template <typename T>
    class UniquePtr {
    private:
        T *ptr_;

    public:
        UniquePtr() noexcept;
        explicit UniquePtr(T *ptr_) noexcept;
        UniquePtr(const UniquePtr &) = delete;
        UniquePtr(UniquePtr &&other) noexcept;

        ~UniquePtr();

        UniquePtr<T> &operator=(const UniquePtr<T> &) = delete;
        UniquePtr<T> &operator=(UniquePtr<T> &&other) noexcept;
        UniquePtr<T> &operator=(std::nullptr_t) noexcept;

        T *release() noexcept;
        void reset(T *ptr = nullptr) noexcept;
        void swap(UniquePtr<T> &other) noexcept;

        T *get() const noexcept;
        explicit operator bool() const noexcept;

        T *operator->() const noexcept;
        T &operator*() const noexcept;

        friend bool operator==(const UniquePtr<T> &x, const UniquePtr<T> &y) noexcept { return x.get() == y.get(); }
        friend bool operator!=(const UniquePtr<T> &x, const UniquePtr<T> &y) noexcept { return !(x == y); }
        friend bool operator==(const UniquePtr<T> &x, std::nullptr_t) noexcept { return !x; }
        friend bool operator==(std::nullptr_t, const UniquePtr<T> &x) noexcept { return !x; }
        friend bool operator!=(const UniquePtr<T> &x, std::nullptr_t) noexcept { return (bool)x; }
        friend bool operator!=(std::nullptr_t, const UniquePtr<T> &x) noexcept { return (bool)x; }
        friend bool operator==(const T *x, const UniquePtr<T> &y) noexcept { return x == y.get(); }
        friend bool operator==(const UniquePtr<T> &x, const T *y) noexcept { return y == x.get(); }
        friend bool operator!=(const T *x, const UniquePtr<T> &y) noexcept { return x != y.get(); }
        friend bool operator!=(const UniquePtr<T> &x, const T *y) noexcept { return y != x.get(); }

        friend void swap(UniquePtr<T> &lhs, UniquePtr<T> &rhs) noexcept { lhs.swap(rhs); }
    };

    template <typename T>
    UniquePtr<T>::UniquePtr() noexcept : ptr_(nullptr) {}

    template <typename T>
    UniquePtr<T>::UniquePtr(T *ptr) noexcept : ptr_(ptr) {}

    template <typename T>
    UniquePtr<T>::UniquePtr(UniquePtr &&other) noexcept : ptr_(other.release()) {}

    template <typename T>
    UniquePtr<T>::~UniquePtr() {
        delete ptr_;
    }

    template <typename T>
    UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr<T> &&other) noexcept {
        if (this != &other)
            reset(other.release());
        return *this;
    }

    template <typename T>
    UniquePtr<T> &UniquePtr<T>::operator=(std::nullptr_t) noexcept {
        reset();
        return *this;
    }

    template <class T>
    T *UniquePtr<T>::release() noexcept {
        T *tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    template <typename T>
    void UniquePtr<T>::reset(T *ptr) noexcept {
        delete ptr_;
        ptr_ = ptr;
    }

    template <typename T>
    void UniquePtr<T>::swap(UniquePtr<T> &other) noexcept {
        T *tmp = ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = tmp;
    }

    template <typename T>
    UniquePtr<T>::operator bool() const noexcept {
        return ptr_ != nullptr;
    }

    template <typename T>
    T *UniquePtr<T>::get() const noexcept {
        return ptr_;
    }

    template <typename T>
    T *UniquePtr<T>::operator->() const noexcept {
        return ptr_;
    }

    template <typename T>
    T &UniquePtr<T>::operator*() const noexcept {
        return *ptr_;
    }

    template <typename T>
    class UniquePtr<T[]> {
    private:
        T *ptr_;

    public:
        UniquePtr() noexcept;
        explicit UniquePtr(T *ptr) noexcept;
        UniquePtr(const UniquePtr &) = delete;
        UniquePtr(UniquePtr<T[]> &&other) noexcept;

        ~UniquePtr();

        UniquePtr<T[]> &operator=(const UniquePtr<T[]> &) = delete;
        UniquePtr<T[]> &operator=(UniquePtr<T[]> &&other) noexcept;
        UniquePtr<T[]> &operator=(std::nullptr_t) noexcept;

        T *release() noexcept;
        void reset(T *ptr = nullptr) noexcept;
        void swap(UniquePtr<T[]> &other) noexcept;

        T *get() const noexcept;
        explicit operator bool() const noexcept;

        T &operator[](std::size_t i) const;

        friend bool operator==(const UniquePtr<T[]> &x, const UniquePtr<T[]> &y) noexcept { return x.get() == y.get(); }
        friend bool operator!=(const UniquePtr<T[]> &x, const UniquePtr<T[]> &y) noexcept { return !(x == y); }
        friend bool operator==(const UniquePtr<T[]> &x, std::nullptr_t) noexcept { return !x; }
        friend bool operator==(std::nullptr_t, const UniquePtr<T[]> &x) noexcept { return !x; }
        friend bool operator!=(const UniquePtr<T[]> &x, std::nullptr_t) noexcept { return (bool)x; }
        friend bool operator!=(std::nullptr_t, const UniquePtr<T[]> &x) noexcept { return (bool)x; }
        friend bool operator==(const T *x, const UniquePtr<T[]> &y) noexcept { return x == y.get(); }
        friend bool operator==(const UniquePtr<T[]> &x, const T *y) noexcept { return y == x.get(); }
        friend bool operator!=(const T *x, const UniquePtr<T[]> &y) noexcept { return x != y.get(); }
        friend bool operator!=(const UniquePtr<T[]> &x, const T *y) noexcept { return y != x.get(); }

        friend void swap(UniquePtr<T[]> &lhs, UniquePtr<T[]> &rhs) noexcept { lhs.swap(rhs); }
    };

    template <typename T>
    UniquePtr<T[]>::UniquePtr() noexcept : ptr_(nullptr) {}

    template <typename T>
    UniquePtr<T[]>::UniquePtr(T *ptr) noexcept : ptr_(ptr) {}

    template <typename T>
    UniquePtr<T[]>::UniquePtr(UniquePtr<T[]> &&other) noexcept : ptr_(other.release()) {}

    template <typename T>
    UniquePtr<T[]>::~UniquePtr() {
        delete[] ptr_;
    }

    template <typename T>
    UniquePtr<T[]> &UniquePtr<T[]>::operator=(UniquePtr<T[]> &&other) noexcept {
        if (this != &other)
            reset(other.release());
        return *this;
    }

    template <typename T>
    UniquePtr<T[]> &UniquePtr<T[]>::operator=(std::nullptr_t) noexcept {
        reset();
        return *this;
    }

    template <typename T>
    T *UniquePtr<T[]>::release() noexcept {
        T *tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    template <typename T>
    void UniquePtr<T[]>::reset(T *ptr) noexcept {
        delete[] ptr_;
        ptr_ = ptr;
    }

    template <typename T>
    void UniquePtr<T[]>::swap(UniquePtr<T[]> &other) noexcept {
        T *tmp = ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = tmp;
    }

    template <typename T>
    T *UniquePtr<T[]>::get() const noexcept {
        return ptr_;
    }

    template <typename T>
    UniquePtr<T[]>::operator bool() const noexcept {
        return ptr_ != nullptr;
    }

    template <typename T>
    T &UniquePtr<T[]>::operator[](std::size_t i) const {
        return ptr_[i];
    }

    template <typename T, typename... Args>
    typename std::enable_if<!std::is_array<T>::value, UniquePtr<T>>::type make_unique(Args &&...args) {
        return UniquePtr<T>(new T(std::forward<Args>(args)...));
    }

    template <typename T>
    typename std::enable_if<std::is_array<T>::value, UniquePtr<T>>::type make_unique(std::size_t size) {
        return UniquePtr<T>(new typename std::remove_extent<T>::type[size]());
    }
} // namespace sem3

#endif // UNIQUE_PTR_HPP
