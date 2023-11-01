#ifndef LAB2CORRECT2_UNITTEST_HPP
#define LAB2CORRECT2_UNITTEST_HPP

#include <string>
#include "../MyExceptions/TestFailedException.hpp"

#define TEST(cluster, name) \
    void cluster##_##name()

#define ASSERT(expression) \
    if (!(expression)) throw myexcept::TestFailedException(#expression, __FILE__,  __FUNCTION__, __LINE__)


namespace test {

    class UnitTest {
    private:
        std::string name;
        void (*TestFunction)();

    public:
        UnitTest(std::string name, void (*TestFunction)());
        [[nodiscard]] bool Run() const;
    };

} // lab2

#endif //LAB2CORRECT2_UNITTEST_HPP
