#ifndef LAB2CORRECT2_TESTRUNNER_HPP
#define LAB2CORRECT2_TESTRUNNER_HPP
#include <vector>
#include "TestCluster.hpp"

namespace test {
    class TestRunner {
    private:
        std::vector<TestCluster> clusters;
    public:
        TestRunner() = default;
        ~TestRunner() = default;

        void AddTestCluster(const TestCluster &cluster);
        void RunTests();
    };
} // test

#endif //LAB2CORRECT2_TESTRUNNER_HPP
