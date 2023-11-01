#include "TestFailedException.hpp"
#include <string>

namespace myexcept {
    TestFailedException::TestFailedException(const std::string &expression,
                                             const std::string &file,
                                             const std::string &function,
                                             int line)
    {
        this->message = "Test failed:" +
                        file + " (" + std::to_string(line) + ") in function \"" +
                        function + "\" : \"" + expression + "\"";
    }

    const char *TestFailedException::what() const noexcept {
        return this->message.c_str();
    }

} // myexcept