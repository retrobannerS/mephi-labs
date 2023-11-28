#include "menu.hpp"
#include "InsertionSorter.hpp"


using namespace std;
using namespace sem3;

int main() {
    //menu<int> my_menu;
    //my_menu.run();

    //test deleting of sorters
    UniquePtr<BaseSorter<int>> sorter(new InsertionSorter<int>(SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>), [](int a, int b) {return a - b;}));
    sorter.reset(new InsertionSorter<int>(SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>), [](int a, int b) {return a - b;}));

    return 0;
}



