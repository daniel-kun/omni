#ifndef OMNI_TESTS_CORE_INPUT_TEST_UTILS_INPUT_HPP
#define OMNI_TESTS_CORE_INPUT_TEST_UTILS_INPUT_HPP

#include <memory>

namespace omni {
namespace core {
namespace input {
class syntax_element;
} // namespace input
} // namespace core
} // namespace omni

namespace omni {
namespace tests {
std::shared_ptr <core::input::syntax_element> makeTestSyntaxElement ();
}
}

#endif // include guard
