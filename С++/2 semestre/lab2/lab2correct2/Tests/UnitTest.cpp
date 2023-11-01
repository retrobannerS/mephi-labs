#include "UnitTest.hpp"

#include <iostream>
#include <utility>
#include <stdexcept>
#include <string>

namespace test {

    UnitTest::UnitTest(std::string name, void (*TestFunction)()) {
        this->name = std::move(name);
        this->TestFunction = TestFunction;
    }

    bool UnitTest::Run() const {
        try {
            TestFunction();
        } catch(std::exception &e) {
            std::cout << "FAILED :" << this->name << std::endl;
            std::cout << e.what() << std::endl;
            return false;
        }
        std::cout << "PASSED: " << this->name << std::endl;
        return true;
    }

} // lab2