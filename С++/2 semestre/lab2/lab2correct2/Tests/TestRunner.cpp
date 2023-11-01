#include "TestRunner.hpp"
#include "TestCluster.hpp"
#include <iostream>

namespace test {
    void TestRunner::AddTestCluster(const TestCluster &cluster) {
        this->clusters.push_back(cluster);
    }

    void TestRunner::RunTests() {
        std::cout << "Running tests..." << std::endl << std::endl;
        size_t passed = 0;
        size_t full = 0;
        for(const auto &cluster : this->clusters) {
            passed += cluster.Run();
            full += cluster.GetSize();
            std::cout << std::endl;
        }
        if(passed == full) {
            std::cout << "All tests passed!" << std::endl;
        } else {
            std::cout << "Failed " << full - passed << " tests." << std::endl;
        }
    }
} // test