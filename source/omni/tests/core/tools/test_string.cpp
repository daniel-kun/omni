#include <omni/core/tools/string.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (stringTests)

BOOST_AUTO_TEST_CASE (startsWith)
{
    using namespace omni::core::tools;
    BOOST_CHECK (starts_with ("asdf", "a"));
    BOOST_CHECK (starts_with ("asdf", "asdf"));
    BOOST_CHECK (starts_with ("", ""));
    BOOST_CHECK (starts_with ("asdf", ""));

    BOOST_CHECK (! starts_with ("asdf", "s"));
    BOOST_CHECK (! starts_with ("asdf", "asdfgh"));
    BOOST_CHECK (! starts_with ("asdf", " a"));
    BOOST_CHECK (! starts_with (" asdf", "a"));
}

BOOST_AUTO_TEST_CASE (isNumeric)
{
    using namespace omni::core::tools;
    BOOST_CHECK (is_numeric ("1"));
    BOOST_CHECK (is_numeric ("1."));
    BOOST_CHECK (is_numeric ("1,000"));
    BOOST_CHECK (is_numeric ("1,000."));
    BOOST_CHECK (is_numeric ("1,000.123"));
    BOOST_CHECK (is_numeric ("1.123"));
    BOOST_CHECK (is_numeric ("12345678901234567890"));
    BOOST_CHECK (is_numeric ("12345678901234567890."));
    BOOST_CHECK (is_numeric ("12345678901234567890.12345"));

    BOOST_CHECK (! is_numeric (" 1"));
    BOOST_CHECK (! is_numeric ("1 "));
    BOOST_CHECK (! is_numeric ("a1"));
    BOOST_CHECK (! is_numeric ("a 1"));
    BOOST_CHECK (! is_numeric ("1a"));
    BOOST_CHECK (! is_numeric ("1 a"));

    // Checking of correct positions of thousands and decimal separator not yet implemented:
    // BOOST_CHECK (! is_numeric ("1,"));
    // BOOST_CHECK (! is_numeric ("1,12"));
    // BOOST_CHECK (! is_numeric ("1,12"));
    // BOOST_CHECK (! is_numeric ("1,123,123,45"));
}

BOOST_AUTO_TEST_SUITE_END ()
