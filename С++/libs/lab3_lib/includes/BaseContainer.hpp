#ifndef LAB3_BASECONTAINER_HPP
#define LAB3_BASECONTAINER_HPP
#include "Sequence.hpp"
#include "Options.hpp"
#include "IEnumerable.hpp"
#include "IEnumerator.hpp"
using namespace lab2;

namespace lab3 {
    template<typename T>
    class BaseContainer : public IEnumerable<T> {
    protected:
        using IEnumerable<T>::sequence;

        BaseContainer();

    public:
        [[nodiscard]] bool empty() const;

        [[nodiscard]] int size() const;

        void clear();

        T reduce(T (*func)(const T &, const T &)) const;
        void slice(int start, int count, const Sequence<T> &sq);
        int find(const Sequence<T> &find_sequence) const;
        Options<int> tryFind(const Sequence<T> &find_sequence) const;
        friend std::ostream &operator<<(std::ostream &out, const BaseContainer<T> &container) {
            if(container.empty()) {
                out << "[ ]";
                return out;
            }
            out << "[";
            for(const auto &item : container) {
                out << item << "; ";
            }
            out << "\b\b]" << std::endl;
            return out;
        }
    };

    template<typename T>
    BaseContainer<T>::BaseContainer() = default;

    template<typename T>
    bool BaseContainer<T>::empty() const {
        return sequence->Empty();
    }

    template<typename T>
    int BaseContainer<T>::size() const {
        return sequence->GetSize();
    }

    template<typename T>
    void BaseContainer<T>::clear() {
        sequence->Clear();
    }

    template<typename T>
    T BaseContainer<T>::reduce(T (*func)(const T &, const T &)) const {
        try {
            return sequence->Reduce(func);
        } catch (std::invalid_argument &e) {
            throw std::invalid_argument("Invalid size!");
        }
    }

    template<typename T>
    void BaseContainer<T>::slice(int start, int count, const Sequence<T> &sq) {
        try {
            sequence->Slice(start, count, sq);
        } catch (std::exception &e) {
            throw std::out_of_range("Index out of range!");
        }
    }

    template<typename T>
    int BaseContainer<T>::find(const Sequence<T> &find_sequence) const {
        if (find_sequence.GetSize() > sequence->GetSize())
            throw std::invalid_argument("Invalid argument!");

        for (int i = 0; i != sequence->GetSize() - find_sequence.GetSize() + 1; ++i) {
            bool found = true;
            for (int j = 0; j < find_sequence.GetSize(); ++j) {
                if ((*sequence).Get(i + j) != find_sequence.Get(j)) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return i;
            }
        }
        throw std::logic_error("Not found!");
    }

    template<typename T>
    Options<int> BaseContainer<T>::tryFind(const Sequence<T> &find_sequence) const {
        if (find_sequence.GetSize() > sequence->GetSize())
            return {};

        for (int i = 0; i != sequence->GetSize() - find_sequence.GetSize() + 1; ++i) {
            bool found = true;
            for (int j = 0; j < find_sequence.GetSize(); ++j) {
                if ((*sequence).Get(i + j) != find_sequence.Get(j)) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return Options<int>(i);
            }
        }
        return {};
    }
}//lab3

#endif //LAB3_BASECONTAINER_HPP
