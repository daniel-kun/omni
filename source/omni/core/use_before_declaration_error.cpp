#include <omni/core/use_before_declaration_error.hpp>

#include <sstream>

namespace {
std::string buildUseBeforeDeclarationErrorMessage (omni::core::domain domain, std::string const & identifier)
{
    std::stringstream result;
    switch (domain) {
    case omni::core::domain::variable:
        result << "Variable " << identifier << " was used, before it was declared.";
        break;
    default:
        result << "Entity" << identifier << " was used, before it was declared.";
    }
    return result.str ();
}
}

omni::core::use_before_declaration_error::use_before_declaration_error (domain domain, std::string const & identifier) :
    std::runtime_error (buildUseBeforeDeclarationErrorMessage (domain, identifier))
{

}
