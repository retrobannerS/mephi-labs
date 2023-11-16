#pragma once

#include "smart_pointers/ControlBlock.hpp"
#include <stdexcept>
#include <utility>

namespace sem3 {
    template <typename T>
    class SharedPtr {
    private:
        ControlBlock<T> *block;

        void update_reference(ControlBlock<T> *new_control_block);

    public:
        SharedPtr() noexcept;
        explicit SharedPtr(T *ptr) noexcept;
        explicit SharedPtr(std::nullptr_t) noexcept;

        SharedPtr(const SharedPtr &other) noexcept;
        SharedPtr(SharedPtr &&other) noexcept;

        ~SharedPtr();

        SharedPtr<T> &operator=(const SharedPtr<T> &other) noexcept;
        SharedPtr<T> &operator=(SharedPtr<T> &&other) noexcept;
        SharedPtr<T> &operator=(std::nullptr_t) noexcept;

        void reset(T *ptr = nullptr) noexcept;
        void swap(SharedPtr<T> &other) noexcept;

        T *get() const noexcept;
        T *operator->() const noexcept;
        T &operator*() const noexcept;
        size_t use_count() const noexcept;
        bool unique() const noexcept;
        explicit operator bool() const noexcept;

        friend bool operator==(const SharedPtr<T> &x, const SharedPtr<T> &y) noexcept { return x.get() == y.get(); }
        friend bool operator!=(const SharedPtr<T> &x, const SharedPtr<T> &y) noexcept { return !(x == y); }
        friend bool operator==(const SharedPtr<T> &x, std::nullptr_t) noexcept { return !x; }
        friend bool operator==(std::nullptr_t, const SharedPtr<T> &x) noexcept { return !x; }
        friend bool operator!=(const SharedPtr<T> &x, std::nullptr_t) noexcept { return (bool)x; }
        friend bool operator!=(std::nullptr_t, const SharedPtr<T> &x) noexcept { return (bool)x; }
        friend bool operator==(const T *x, const SharedPtr<T> &y) noexcept { return x == y.get(); }
        friend bool operator==(const SharedPtr<T> &x, const T *y) noexcept { return y == x.get(); }
        friend bool operator!=(const T *x, const SharedPtr<T> &y) noexcept { return x != y.get(); }
        friend bool operator!=(const SharedPtr<T> &x, const T *y) noexcept { return y != x.get(); }

        friend void swap(SharedPtr<T> &lhs, SharedPtr<T> &rhs) noexcept { lhs.swap(rhs); }
    };

    template <typename T>
    void SharedPtr<T>::update_reference(ControlBlock<T> *new_block) {
        if (block)
            block->decrement_ref_count_and_delete_if_0();
        block = new_block;
    }

    template <typename T>
    SharedPtr<T>::SharedPtr() noexcept : block(nullptr) {}

    template <typename T>
    SharedPtr<T>::SharedPtr(T *ptr) noexcept : block(new ControlBlock<T>(ptr)) {}

    template <typename T>
    SharedPtr<T>::SharedPtr(std::nullptr_t) noexcept : block(nullptr) {}

    template <typename T>
    SharedPtr<T>::SharedPtr(const SharedPtr &other) noexcept : block(other.block) {
        if (block && block->get() != nullptr)
            block->increment_ref_count();
    }

    template <typename T>
    SharedPtr<T>::SharedPtr(SharedPtr &&other) noexcept : block(other.block) {
        other.block = nullptr;
    }

    template <typename T>
    SharedPtr<T>::~SharedPtr() {
        update_reference(nullptr);
    }

    template <typename T>
    SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &other) noexcept {
        if (this != &other) {
            update_reference(other.block);
            if (block && block->get() != nullptr)
                block->increment_ref_count();
        }
        return *this;
    }

    template <typename T>
    SharedPtr<T> &SharedPtr<T>::operator=(SharedPtr<T> &&other) noexcept {
        if (this != &other) {
            update_reference(other.block);
            other.block = nullptr;
        }
        return *this;
    }

    template <typename T>
    SharedPtr<T> &SharedPtr<T>::operator=(std::nullptr_t) noexcept {
        update_reference(nullptr);
        return *this;
    }

    template <typename T>
    void SharedPtr<T>::reset(T *ptr) noexcept {
        if (ptr != nullptr)
            update_reference(new ControlBlock<T>(ptr));
        else
            update_reference(nullptr);
    }

    template <typename T>
    void SharedPtr<T>::swap(SharedPtr<T> &other) noexcept {
        ControlBlock<T> *tmp = std::move(other.block);
        other.block = std::move(block);
        block = std::move(tmp);
    }

    template <typename T>
    T *SharedPtr<T>::get() const noexcept {
        if (block == nullptr)
            return nullptr;
        return block->get();
    }

    template <typename T>
    T *SharedPtr<T>::operator->() const noexcept {
        return get();
    }

    template <typename T>
    T &SharedPtr<T>::operator*() const noexcept {
        return *(get());
    }

    template <typename T>
    size_t SharedPtr<T>::use_count() const noexcept {
        if (block == nullptr)
            return 0;
        return block->get_ref_count();
    }

    template <typename T>
    bool SharedPtr<T>::unique() const noexcept {
        return use_count() == 1;
    }

    template <typename T>
    SharedPtr<T>::operator bool() const noexcept {
        return get() != nullptr;
    }

    template <typename T>
    class SharedPtr<T[]> {
    private:
        ControlBlock<T[]> *block;

        void update_reference(ControlBlock<T[]> *new_control_block);

    public:
        SharedPtr() noexcept;
        explicit SharedPtr(T *ptr) noexcept;
        explicit SharedPtr(std::nullptr_t) noexcept;

        SharedPtr(const SharedPtr &other) noexcept;
        SharedPtr(SharedPtr &&other) noexcept;

        ~SharedPtr();

        SharedPtr<T[]> &operator=(const SharedPtr<T[]> &other) noexcept;
        SharedPtr<T[]> &operator=(SharedPtr<T[]> &&other) noexcept;
        SharedPtr<T[]> &operator=(std::nullptr_t) noexcept;

        void reset(T *ptr = nullptr) noexcept;
        void swap(SharedPtr<T[]> &other) noexcept;

        T *get() const noexcept;
        T &operator[](std::size_t index) const;
        size_t use_count() const noexcept;
        bool unique() const noexcept;
        explicit operator bool() const noexcept;

        friend bool operator==(const SharedPtr<T[]> &x, const SharedPtr<T[]> &y) noexcept { return x.get() == y.get(); }
        friend bool operator!=(const SharedPtr<T[]> &x, const SharedPtr<T[]> &y) noexcept { return !(x == y); }
        friend bool operator==(const SharedPtr<T[]> &x, std::nullptr_t) noexcept { return !x; }
        friend bool operator==(std::nullptr_t, const SharedPtr<T[]> &x) noexcept { return !x; }
        friend bool operator!=(const SharedPtr<T[]> &x, std::nullptr_t) noexcept { return (bool)x; }
        friend bool operator!=(std::nullptr_t, const SharedPtr<T[]> &x) noexcept { return (bool)x; }
        friend bool operator==(const T *x, const SharedPtr<T[]> &y) noexcept { return x == y.get(); }
        friend bool operator==(const SharedPtr<T[]> &x, const T *y) noexcept { return y == x.get(); }
        friend bool operator!=(const T *x, const SharedPtr<T[]> &y) noexcept { return x != y.get(); }
        friend bool operator!=(const SharedPtr<T[]> &x, const T *y) noexcept { return y != x.get(); }

        friend void swap(SharedPtr<T[]> &lhs, SharedPtr<T[]> &rhs) noexcept { lhs.swap(rhs); }
    };

    template <typename T>
    void SharedPtr<T[]>::update_reference(ControlBlock<T[]> *new_block) {
        if (block)
            block->decrement_ref_count_and_delete_if_0();
        block = new_block;
    }

    template <typename T>
    SharedPtr<T[]>::SharedPtr() noexcept : block(nullptr) {}

    template <typename T>
    SharedPtr<T[]>::SharedPtr(T *ptr) noexcept : block(new ControlBlock<T[]>(ptr)) {}

    template <typename T>
    SharedPtr<T[]>::SharedPtr(std::nullptr_t) noexcept : block(nullptr) {}

    template <typename T>
    SharedPtr<T[]>::SharedPtr(const SharedPtr &other) noexcept : block(other.block) {
        if (block && block->get() != nullptr)
            block->increment_ref_count();
    }

    template <typename T>
    SharedPtr<T[]>::SharedPtr(SharedPtr &&other) noexcept : block(other.block) {
        other.block = nullptr;
    }

    template <typename T>
    SharedPtr<T[]>::~SharedPtr() {
        update_reference(nullptr);
    }

    template <typename T>
    SharedPtr<T[]> &SharedPtr<T[]>::operator=(const SharedPtr<T[]> &other) noexcept {
        if (this != &other) {
            update_reference(other.block);
            if (block && block->get() != nullptr)
                block->increment_ref_count();
        }
        return *this;
    }

    template <typename T>
    SharedPtr<T[]> &SharedPtr<T[]>::operator=(SharedPtr<T[]> &&other) noexcept {
        if (this != &other) {
            update_reference(other.block);
            other.block = nullptr;
        }
        return *this;
    }

    template <typename T>
    SharedPtr<T[]> &SharedPtr<T[]>::operator=(std::nullptr_t) noexcept {
        update_reference(nullptr);
        return *this;
    }

    template <typename T>
    void SharedPtr<T[]>::reset(T *ptr) noexcept {
        if (ptr != nullptr)
            update_reference(new ControlBlock<T[]>(ptr));
        else
            update_reference(nullptr);
    }

    template <typename T>
    void SharedPtr<T[]>::swap(SharedPtr<T[]> &other) noexcept {
        ControlBlock<T[]> *tmp = std::move(other.block);
        other.block = std::move(block);
        block = std::move(tmp);
    }

    template <typename T>
    T *SharedPtr<T[]>::get() const noexcept {
        if (block == nullptr)
            return nullptr;
        return block->get();
    }

    template <typename T>
    T &SharedPtr<T[]>::operator[](std::size_t index) const {
        return get()[index];
    }

    template <typename T>
    size_t SharedPtr<T[]>::use_count() const noexcept {
        if (block == nullptr)
            return 0;
        return block->get_ref_count();
    }

    template <typename T>
    bool SharedPtr<T[]>::unique() const noexcept {
        return use_count() == 1;
    }

    template <typename T>
    SharedPtr<T[]>::operator bool() const noexcept {
        return get() != nullptr;
    }

    template <class T, class... Args>
    typename std::enable_if<!std::is_array<T>::value, SharedPtr<T>>::type make_shared(Args &&...args) {
        return SharedPtr<T>(new T(std::forward<Args>(args)...));
    }

    template <class T>
    typename std::enable_if<std::is_array<T>::value, SharedPtr<T>>::type make_shared(std::size_t size) {
        return SharedPtr<T>(new typename std::remove_extent<T>::type[size]());
    }

} // namespace sem3