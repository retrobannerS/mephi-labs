#include "TestCluster.hpp"

#include <string>
#include <vector>
#include <iostream>

namespace test {
    TestCluster::TestCluster(const std::string &name) {
        this->name = name;
    }

    size_t TestCluster::GetSize() const {
        return tests.size();
    }

    bool TestCluster::AddTest(const test::UnitTest &test) {
        tests.push_back(test);
        return false;
    }

    size_t TestCluster::Run() const {
        std::cout<< "Cluster \"" << this->name << "\" is running..." << std::endl;
        size_t passed_tests_counter = 0;
        for (auto &test : this->tests) {
            passed_tests_counter += (size_t)test.Run();
        }

        if(passed_tests_counter == this->GetSize()){
            std::cout << "Cluster \"" << this->name << "\" passed all tests!" << std::endl;
        } else {
            std::cout << "Cluster \"" << this->name << "\" failed " << \
            this->GetSize() - passed_tests_counter << " tests!" << std::endl;
        }
        return passed_tests_counter;
    }

} // lab2