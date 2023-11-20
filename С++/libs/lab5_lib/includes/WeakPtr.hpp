#pragma once
#include "ControlBlock.hpp"
#include <utility>

namespace sem3 {

    template <typename T>
    class SharedPtr;

    template <typename T>
    class WeakPtr {
    private:
        ControlBlock<T> *block;
        void update_reference(ControlBlock<T> *new_block);

        friend class SharedPtr<T>;

    public:
        WeakPtr() noexcept;
        WeakPtr(const WeakPtr &other) noexcept;
        explicit WeakPtr(const SharedPtr<T> &other) noexcept;
        WeakPtr(WeakPtr &&other) noexcept;

        ~WeakPtr();

        WeakPtr<T> &operator=(const WeakPtr<T> &other) noexcept;
        WeakPtr<T> &operator=(const SharedPtr<T> &other) noexcept;
        WeakPtr<T> &operator=(WeakPtr<T> &&other) noexcept;
        WeakPtr<T> &operator=(std::nullptr_t) noexcept;

        void reset() noexcept;
        void swap(WeakPtr<T> &other) noexcept;

        [[nodiscard]] unsigned int use_count() const noexcept;
        [[nodiscard]] bool expired() const noexcept;
        SharedPtr<T> lock() const noexcept;

        friend void swap(WeakPtr<T> &lhs, WeakPtr<T> &rhs) noexcept { lhs.swap(rhs); }
    };

    template <typename T>
    void WeakPtr<T>::update_reference(ControlBlock<T> *new_block) {
        if (block) {
            block->decrement_weak_ref_count_and_delete_if_0();
        }
        block = new_block;
    }

    template <typename T>
    WeakPtr<T>::WeakPtr() noexcept : block(nullptr) {}

    template <typename T>
    WeakPtr<T>::WeakPtr(const WeakPtr &other) noexcept : block(other.block) {
        if (block) {
            block->increment_weak_ref_count();
        }
    }

    template <typename T>
    WeakPtr<T>::WeakPtr(const SharedPtr<T> &other) noexcept : block(other.block) {
        if (block) {
            block->increment_weak_ref_count();
        }
    }

    template <typename T>
    WeakPtr<T>::WeakPtr(WeakPtr &&other) noexcept : block(other.block) {
        other.block = nullptr;
    }

    template <typename T>
    WeakPtr<T>::~WeakPtr() {
        update_reference(nullptr);
    }

    template <typename T>
    WeakPtr<T> &WeakPtr<T>::operator=(const WeakPtr<T> &other) noexcept {
        if (this != &other) {
            update_reference(other.block);
            if (block && block->get() != nullptr)
                block->increment_weak_ref_count();
        }
        return *this;
    }

    template <typename T>
    WeakPtr<T> &WeakPtr<T>::operator=(const SharedPtr<T> &other) noexcept {
        update_reference(other.block);
        if (block && block->get() != nullptr)
            block->increment_weak_ref_count();
        return *this;
    }

    template <typename T>
    WeakPtr<T> &WeakPtr<T>::operator=(WeakPtr<T> &&other) noexcept {
        if (this != &other) {
            update_reference(other.block);
            other.block = nullptr;
        }
        return *this;
    }

    template <typename T>
    WeakPtr<T> &WeakPtr<T>::operator=(std::nullptr_t) noexcept {
        update_reference(nullptr);
        return *this;
    }

    template <typename T>
    void WeakPtr<T>::reset() noexcept {
        update_reference(nullptr);
    }

    template <typename T>
    void WeakPtr<T>::swap(WeakPtr<T> &other) noexcept {
        std::swap(block, other.block);
    }

    template <typename T>
    [[nodiscard]] unsigned int WeakPtr<T>::use_count() const noexcept {
        return block ? block->get_ref_count() : 0;
    }

    template <typename T>
    bool WeakPtr<T>::expired() const noexcept {
        return use_count() == 0;
    }

    template <typename T>
    SharedPtr<T> WeakPtr<T>::lock() const noexcept {
        return expired() ? SharedPtr<T>() : SharedPtr<T>(*this);
    }

    template <typename T>
    class WeakPtr<T[]> {
    private:
        ControlBlock<T[]> *block;
        void update_reference(ControlBlock<T[]> *new_block);

        friend class SharedPtr<T[]>;

    public:
        WeakPtr() noexcept;
        WeakPtr(const WeakPtr &other) noexcept;
        explicit WeakPtr(const SharedPtr<T[]> &other) noexcept;
        WeakPtr(WeakPtr &&other) noexcept;

        ~WeakPtr();

        WeakPtr<T[]> &operator=(const WeakPtr<T[]> &other) noexcept;
        WeakPtr<T[]> &operator=(const SharedPtr<T[]> &other) noexcept;
        WeakPtr<T[]> &operator=(WeakPtr<T[]> &&other) noexcept;
        WeakPtr<T[]> &operator=(std::nullptr_t) noexcept;

        void reset() noexcept;
        void swap(WeakPtr<T[]> &other) noexcept;

        [[nodiscard]] unsigned int use_count() const noexcept;
        [[nodiscard]] bool expired() const noexcept;
        SharedPtr<T[]> lock() const noexcept;

        friend void swap(WeakPtr<T[]> &lhs, WeakPtr<T[]> &rhs) noexcept { lhs.swap(rhs); }
    };

    template <typename T>
    void WeakPtr<T[]>::update_reference(ControlBlock<T[]> *new_block) {
        if (block) {
            block->decrement_weak_ref_count_and_delete_if_0();
        }
        block = new_block;
    }

    template <typename T>
    WeakPtr<T[]>::WeakPtr() noexcept : block(nullptr) {}

    template <typename T>
    WeakPtr<T[]>::WeakPtr(const WeakPtr &other) noexcept : block(other.block) {
        if (block) {
            block->increment_weak_ref_count();
        }
    }

    template <typename T>
    WeakPtr<T[]>::WeakPtr(const SharedPtr<T[]> &other) noexcept : block(other.block) {
        if (block) {
            block->increment_weak_ref_count();
        }
    }

    template <typename T>
    WeakPtr<T[]>::WeakPtr(WeakPtr &&other) noexcept : block(other.block) {
        other.block = nullptr;
    }

    template <typename T>
    WeakPtr<T[]>::~WeakPtr() {
        update_reference(nullptr);
    }

    template <typename T>
    WeakPtr<T[]> &WeakPtr<T[]>::operator=(const WeakPtr<T[]> &other) noexcept {
        if (this != &other) {
            update_reference(other.block);
            if (block && block->get() != nullptr)
                block->increment_weak_ref_count();
        }
        return *this;
    }

    template <typename T>
    WeakPtr<T[]> &WeakPtr<T[]>::operator=(const SharedPtr<T[]> &other) noexcept {
        update_reference(other.block);
        if (block && block->get() != nullptr)
            block->increment_weak_ref_count();
        return *this;
    }

    template <typename T>
    WeakPtr<T[]> &WeakPtr<T[]>::operator=(WeakPtr<T[]> &&other) noexcept {
        if (this != &other) {
            update_reference(other.block);
            other.block = nullptr;
        }
        return *this;
    }

    template <typename T>
    WeakPtr<T[]> &WeakPtr<T[]>::operator=(std::nullptr_t) noexcept {
        update_reference(nullptr);
        return *this;
    }

    template <typename T>
    void WeakPtr<T[]>::reset() noexcept {
        update_reference(nullptr);
    }

    template <typename T>
    void WeakPtr<T[]>::swap(WeakPtr<T[]> &other) noexcept {
        std::swap(block, other.block);
    }

    template <typename T>
    [[nodiscard]] unsigned int WeakPtr<T[]>::use_count() const noexcept {
        return block ? block->get_ref_count() : 0;
    }

    template <typename T>
    bool WeakPtr<T[]>::expired() const noexcept {
        return use_count() == 0;
    }

    template <typename T>
    SharedPtr<T[]> WeakPtr<T[]>::lock() const noexcept {
        return expired() ? SharedPtr<T[]>() : SharedPtr<T[]>(*this);
    }

} // namespace sem3