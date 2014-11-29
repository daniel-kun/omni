#include <omni/core/tools/string.hpp>

#include <cctype>
#include <algorithm>

/**
@brief Returns true, wenn `string' starts with the text `startText'.

Always returns true, wenn startText is an empty string.
@param string The string that is tested whether it starts with `startText'.
@param startText The text that string should start with.
@return True, wenn `string' starts with the text `startText'. False otherwise.
**/
bool omni::core::tools::starts_with (std::string const & string, std::string const & startText)
{
    if (string.size () < startText.size ()) {
        return false;
    }
    for (std::size_t i = 0u; i < startText.size (); ++ i) {
        if (startText [i] != string [i]) {
            return false;
        }
    }
    return true;
}

/**
@brief Returns true, when text can be interpreted as a numeric value.

This includes simple digit-only text like 123, but also text with decimal and thousands separators like 1,234.5678.
@param text The text that is checked for numerical content.
@return True, when text can be interpreted as a numeric value.
**/
bool omni::core::tools::is_numeric (std::string const & text)
{
    return std::find_if (text.begin (), text.end (), [] (char p) { return ! std::isdigit (p) && p != '.' && p != ','; }) == text.end ();
}
