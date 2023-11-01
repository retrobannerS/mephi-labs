#ifndef LAB2CORRECT2_TESTFAILEDEXCEPTION_HPP
#define LAB2CORRECT2_TESTFAILEDEXCEPTION_HPP
#include <stdexcept>
#include <string>

namespace myexcept {

    class TestFailedException : public std::exception {
    private:
        std::string message;
    public:
        TestFailedException(const std::string &expression,
                            const std::string &file,
                            const std::string &function,
                            int line);
        [[nodiscard]] const char *what() const noexcept override;
    };

} // myexcept

#endif //LAB2CORRECT2_TESTFAILEDEXCEPTION_HPP
