#pragma once
#include "BaseSorter.hpp"
#include "BinaryInsertionSorter.hpp"
#include "BubbleSorter.hpp"
#include "CocktailSorter.hpp"
#include "CombSorter.hpp"
#include "CountingSorter.hpp"
#include "CycleSorter.hpp"
#include "DoubleSelectionSorter.hpp"
#include "GnomeSorter.hpp"
#include "HeapSorter.hpp"
#include "InsertionByTreeSorter.hpp"
#include "InsertionSorter.hpp"
#include "MergeSorter.hpp"
#include "OddEvenSorter.hpp"
#include "QuickSorter.hpp"
#include "RadixSorter.hpp"
#include "SelectionSorter.hpp"
#include "ShellSorter.hpp"
#include <chrono>
#include <iostream>
#include <string>

using namespace std;

namespace sem3 {
    template <typename T>
    class menu {
    private:
        SharedPtr<SmartSequence<T>> sequence;
        int (*cmp)(T, T);
        int mode;
        UniquePtr<BaseSorter<T>> sorter;
        std::string sorterName;
        bool check_time;

        void print_sorters();
        void print_comparators();
        void print_modes();
        void print_check_time();
        void print_actions();

        void switch_sorter();
        void switch_comparator();
        void switch_mode();
        void switch_size();
        void switch_check_time();
        int switch_actions();

        void print_condition();
        void sort();

        void print_separator();
        void printSequence();
        void generateRandomSequence();
        void generateReversedSequence();
        size_t measureSortingTime();

    public:
        menu() {
            sequence.reset(new SmartArraySequence<T>());
            cmp = [](T a, T b) -> int { return a - b; };
            mode = 1;
            sorter.reset(new InsertionSorter<T>(sequence, cmp));
            sorterName = "InsertionSort";
            check_time = false;
        }
        void run();
    };

    template <typename T>
    void menu<T>::print_sorters() {
        cout << "Sorting Algorithms Menu:" << endl;
        cout << "1. BinaryInsertionSort" << endl;
        cout << "2. BubbleSort" << endl;
        cout << "3. CocktailSort" << endl;
        cout << "4. CombSort" << endl;
        cout << "5. CountingSort" << endl;
        cout << "6. CycleSort" << endl;
        cout << "7. DoubleSelectionSort" << endl;
        cout << "8. GnomeSort" << endl;
        cout << "9. HeapSort" << endl;
        cout << "10. InsertionByTreeSort" << endl;
        cout << "11. InsertionSort" << endl;
        cout << "12. MergeSort" << endl;
        cout << "13. OddEvenSort" << endl;
        cout << "14. QuickSort" << endl;
        cout << "15. RadixSort" << endl;
        cout << "16. SelectionSort" << endl;
        cout << "17. ShellSort" << endl;

        cout << "Enter the corresponding number to choose a sorting algorithm: ";
    }

    template <typename T>
    void menu<T>::print_comparators() {
        cout << "Comparator Menu:" << endl;
        cout << "1. Ascending" << endl;
        cout << "2. Descending" << endl;

        cout << "Enter the corresponding number to choose a comparator: ";
    }

    template <typename T>
    void menu<T>::print_modes() {
        cout << "Mode Menu:" << endl;
        cout << "1. Random" << endl;
        cout << "2. Reversed" << endl;

        cout << "Enter the corresponding number to choose a mode: ";
    }

    template <typename T>
    void menu<T>::print_check_time() {
        cout << "Check time Menu:" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;

        cout << "Enter the corresponding number to choose a mode: ";
    }

    template <typename T>
    void menu<T>::print_actions() {
        cout << "Actions Menu:" << endl;
        cout << "1. Sort" << endl;
        cout << "2. Change the sorting algorithm" << endl;
        cout << "3. Change the comparator" << endl;
        cout << "4. Change the mode" << endl;
        cout << "5. Change the size" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter the corresponding number to choose an action: ";
    }

    template <typename T>
    void menu<T>::switch_sorter() {

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            sorter.reset(new BinaryInsertionSorter<T>(sequence, cmp));
            sorterName = "BinaryInsertionSort";
            break;
        }
        case 2: {
            sorter.reset(new BubbleSorter<T>(sequence, cmp));
            sorterName = "BubbleSort";
            break;
        }
        case 3: {
            sorter.reset(new CocktailSorter<T>(sequence, cmp));
            sorterName = "CocktailSort";
            break;
        }
        case 4: {
            sorter.reset(new CombSorter<T>(sequence, cmp));
            sorterName = "CombSort";
            break;
        }
        case 5: {
            sorter.reset(new CountingSorter<T>(sequence, cmp));
            sorterName = "CountingSort";
            break;
        }
        case 6: {
            sorter.reset(new CycleSorter<T>(sequence, cmp));
            sorterName = "CycleSort";
            break;
        }
        case 7: {
            sorter.reset(new DoubleSelectionSorter<T>(sequence, cmp));
            sorterName = "DoubleSelectionSort";
            break;
        }
        case 8: {
            sorter.reset(new GnomeSorter<T>(sequence, cmp));
            sorterName = "GnomeSort";
            break;
        }
        case 9: {
            sorter.reset(new HeapSorter<T>(sequence, cmp));
            sorterName = "HeapSort";
            break;
        }
        case 10: {
            sorter.reset(new InsertionByTreeSorter<T>(sequence, cmp));
            sorterName = "InsertionByTreeSort";
            break;
        }
        case 11: {
            sorter.reset(new InsertionSorter<T>(sequence, cmp));
            sorterName = "InsertionSort";
            break;
        }
        case 12: {
            sorter.reset(new MergeSorter<T>(sequence, cmp));
            sorterName = "MergeSort";
            break;
        }
        case 13: {
            sorter.reset(new OddEvenSorter<T>(sequence, cmp));
            sorterName = "OddEvenSort";
            break;
        }
        case 14: {
            sorter.reset(new QuickSorter<T>(sequence, cmp));
            sorterName = "QuickSort";
            break;
        }
        case 15: {
            sorter.reset(new RadixSorter<T>(sequence, cmp));
            sorterName = "RadixSort";
            break;
        }
        case 16: {
            sorter.reset(new SelectionSorter<T>(sequence, cmp));
            sorterName = "SelectionSort";
            break;
        }
        case 17: {
            sorter.reset(new ShellSorter<T>(sequence, cmp));
            sorterName = "ShellSort";
            break;
        }
        default:
            cout << "Invalid number." << endl;
        }
    }

    template <typename T>
    void menu<T>::switch_comparator() {
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cmp = [](T a, T b) -> int { return a - b; };
            break;
        }
        case 2: {
            cmp = [](T a, T b) -> int { return b - a; };
            break;
        }
        default:
            cout << "Invalid number." << endl;
        }

        (*sorter).set_cmp(cmp);
    }

    template <typename T>
    void menu<T>::switch_mode() {
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            mode = 1;
            break;
        }
        case 2: {
            mode = 2;
            break;
        }
        default:
            cout << "Invalid number." << endl;
        }
    }

    template <typename T>
    void menu<T>::switch_size() {
        int size;
        cout << "Enter the size of the array: ";
        cin >> size;
        if (size < 0) {
            cout << "Invalid size." << endl;
            return;
        }
        sequence.reset(new SmartArraySequence<T>(size));
        (*sorter).set_arr(sequence);
    }

    template <typename T>
    void menu<T>::switch_check_time() {
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            check_time = true;
            break;
        }
        case 2: {
            check_time = false;
            break;
        }
        default:
            cout << "Invalid number." << endl;
        }
    }

    template <typename T>
    int menu<T>::switch_actions() {
        int choice;
        cin >> choice;

        print_separator();

        switch (choice) {
        case 1: {
            sort();
            break;
        }
        case 2: {
            print_sorters();
            switch_sorter();
            break;
        }
        case 3: {
            print_comparators();
            switch_comparator();
            break;
        }
        case 4: {
            print_modes();
            switch_mode();
            break;
        }
        case 5: {
            switch_size();
            break;
        }
        case 6: {
            return 0;
        }
        default:
            cout << "Invalid number." << endl;
        }
        return 1;
    }

    template <typename T>
    void menu<T>::print_condition() {
        cout << "Sorting Algorithm: " << sorterName << endl;
        cout << "Comparator: " << (cmp(1, 2) > 0 ? "Descending" : "Ascending") << endl;
        cout << "Mode: " << (mode == 1 ? "Random" : "Reversed") << endl;
        cout << "Size: " << sequence->getSize() << endl;
    }

    template <typename T>
    void menu<T>::sort() {
        if (mode == 1) {
            generateRandomSequence();
        } else {
            generateReversedSequence();
        }

        cout << "Original sequence: ";
        printSequence();
        cout << endl;

        size_t time;

        if (check_time) {
            time = measureSortingTime();
        } else {
            (*sorter).sort();
        }

        cout << "Sorted sequence: ";
        printSequence();
        cout << endl;

        if (check_time) {
            cout << "Time: " << time << " microseconds" << endl;
        }
    }

    template <typename T>
    void menu<T>::print_separator() {
        cout << endl << "----------------------------------------" << endl << endl;
    }

    template <typename T>
    void menu<T>::printSequence() {
        for (int i = 0; i < sequence->getSize(); ++i) {
            cout << sequence->get(i) << " ";
        }
        cout << endl;
    }

    template <typename T>
    void menu<T>::generateRandomSequence() {
        srand(time(NULL));
        for (int i = 0; i < sequence->getSize(); ++i) {
            sequence->set(i, rand() % sequence->getSize());
        }
    }

    template <typename T>
    void menu<T>::generateReversedSequence() {
        if (cmp(1, 2) > 0) {
            for (int i = 0; i < sequence->getSize(); ++i) {
                sequence->set(i, i);
            }
        } else {
            for (int i = 0; i < sequence->getSize(); ++i) {
                sequence->set(i, sequence->getSize() - i);
            }
        }
    }

    template <typename T>
    size_t menu<T>::measureSortingTime() {
        auto start_time = chrono::high_resolution_clock::now();
        (*sorter).sort();
        auto end_time = chrono::high_resolution_clock::now();

        return chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    }

    template <typename T>
    void menu<T>::run() {
        print_sorters();
        switch_sorter();
        print_separator();
        print_comparators();
        switch_comparator();
        print_separator();
        print_modes();
        switch_mode();
        print_separator();
        switch_size();
        print_separator();
        print_check_time();
        switch_check_time();
        print_separator();

        while (true) {
            print_condition();
            print_separator();
            print_actions();
            if (!switch_actions()) {
                break;
            }
            print_separator();
        }
    }
} // namespace sem3