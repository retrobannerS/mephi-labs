#include "Tests/TestRunner.hpp"
#include "Tests/DynamicArrayTests/DynamicArrayTests.hpp"
#include "Tests/LinkedListTests/LinkedListTests.hpp"
#include "Tests/ArraySequenceTests/ArraySequenceTests.hpp"
#include "Tests/ListSequenceTests/ListSequenceTests.hpp"

int main() {
    test::TestRunner runner;
    runner.AddTestCluster(DynamicArrayTests);
    runner.AddTestCluster(LinkedListTests);
    runner.AddTestCluster(ArraySequenceTests);
    runner.AddTestCluster(ListSequenceTests);
    runner.RunTests();
    return 0;
}
