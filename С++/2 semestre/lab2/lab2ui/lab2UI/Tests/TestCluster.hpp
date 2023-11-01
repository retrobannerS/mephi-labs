#ifndef LAB2CORRECT2_TESTCLUSTER_HPP
#define LAB2CORRECT2_TESTCLUSTER_HPP

#include <string>
#include <vector>
#include "UnitTest.hpp"

namespace test {

    class TestCluster {
    private:
        std::string name;
        std::vector<UnitTest> tests;
    public:
        explicit TestCluster(const std::string &name);
        bool AddTest(const UnitTest &test);
        [[nodiscard]] size_t GetSize() const;
        [[nodiscard]] size_t Run() const;
    };

} // lab2

#define ADD_TEST(cluster, name) \
    bool tmp_##cluster##_##name = cluster.AddTest(test::UnitTest(#name, cluster##_##name))

#endif //LAB2CORRECT2_TESTCLUSTER_HPP
