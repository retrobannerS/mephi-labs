#pragma once
#include <cstddef>
#include <stdexcept>

namespace sem3 {
    template <typename T>
    class ControlBlock {
    private:
        T *ptr_;
        size_t ref_count;
        size_t weak_ref_count;

    public:
        explicit ControlBlock(T *ptr);

        void increment_ref_count() noexcept;
        void decrement_ref_count_and_delete_if_0();

        void increment_weak_ref_count() noexcept;
        void decrement_weak_ref_count_and_delete_if_0();

        T *get() const noexcept;
        [[nodiscard]] size_t get_ref_count() const noexcept;
        [[nodiscard]] size_t get_weak_ref_count() const noexcept;
    };

    template <typename T>
    ControlBlock<T>::ControlBlock(T *ptr) {
        if (!ptr)
            throw std::invalid_argument("nullptr is in control block constructor");

        ptr_ = ptr;
        ref_count = 1;
        weak_ref_count = 0;
    }

    template <typename T>
    void ControlBlock<T>::increment_ref_count() noexcept {
        ++ref_count;
    }

    template <typename T>
    void ControlBlock<T>::decrement_ref_count_and_delete_if_0() {
        if (ref_count == 0)
            throw std::logic_error("reference count == 0");

        if (ref_count == 1 && ptr_ != nullptr) {
            delete ptr_;
            ptr_ = nullptr;
        }
        --ref_count;
        if (ref_count + weak_ref_count == 0)
            delete this;
    }

    template <typename T>
    void ControlBlock<T>::increment_weak_ref_count() noexcept {
        ++weak_ref_count;
    }

    template <typename T>
    void ControlBlock<T>::decrement_weak_ref_count_and_delete_if_0() {
        if (weak_ref_count == 0)
            throw std::logic_error("weak reference count is zero");

        --weak_ref_count;
        if (ref_count + weak_ref_count == 0)
            delete this;
    }

    template <typename T>
    T *ControlBlock<T>::get() const noexcept {
        return ptr_;
    }

    template <typename T>
    size_t ControlBlock<T>::get_ref_count() const noexcept {
        return ref_count;
    }

    template <typename T>
    size_t ControlBlock<T>::get_weak_ref_count() const noexcept {
        return weak_ref_count;
    }

    template <typename T>
    class ControlBlock<T[]> {
    private:
        T *ptr_;
        size_t ref_count;
        size_t weak_ref_count;

    public:
        explicit ControlBlock(T *ptr);

        void increment_ref_count() noexcept;
        void decrement_ref_count_and_delete_if_0();

        void increment_weak_ref_count() noexcept;
        void decrement_weak_ref_count_and_delete_if_0();

        T *get() const noexcept;
        [[nodiscard]] size_t get_ref_count() const noexcept;
        [[nodiscard]] size_t get_weak_ref_count() const noexcept;
    };

    template <typename T>
    ControlBlock<T[]>::ControlBlock(T *ptr) {
        if (!ptr)
            throw std::invalid_argument("nullptr is in control block constructor");

        ptr_ = ptr;
        ref_count = 1;
        weak_ref_count = 0;
    }

    template <typename T>
    void ControlBlock<T[]>::increment_ref_count() noexcept {
        ++ref_count;
    }

    template <typename T>
    void ControlBlock<T[]>::decrement_ref_count_and_delete_if_0() {
        if (ref_count == 0)
            throw std::logic_error("reference count == 0");

        if (ref_count == 1 && ptr_ != nullptr) {
            delete[] ptr_;
            ptr_ = nullptr;
        }

        --ref_count;
        if (ref_count + weak_ref_count == 0)
            delete this;
    }

    template <typename T>
    void ControlBlock<T[]>::increment_weak_ref_count() noexcept {
        ++weak_ref_count;
    }

    template <typename T>
    void ControlBlock<T[]>::decrement_weak_ref_count_and_delete_if_0() {
        if (weak_ref_count == 0)
            throw std::logic_error("weak reference count is zero");

        --weak_ref_count;
        if (ref_count + weak_ref_count == 0)
            delete this;
    }

    template <typename T>
    T *ControlBlock<T[]>::get() const noexcept {
        return ptr_;
    }

    template <typename T>
    size_t ControlBlock<T[]>::get_ref_count() const noexcept {
        return ref_count;
    }

    template <typename T>
    size_t ControlBlock<T[]>::get_weak_ref_count() const noexcept {
        return weak_ref_count;
    }

} // namespace sem3