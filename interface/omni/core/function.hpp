#ifndef OMNI_CORE_FUNCTION_HPP
#define OMNI_CORE_FUNCTION_HPP

#include <omni/core/core.hpp>
#include <omni/core/object.hpp>
#include <string>

// class definition

namespace omni {
namespace core {

class type;
class function_impl;

class OMNI_CORE_API function : public omni::core::object {
public:
    function (type & type, std::string const & name);

    void setName (std::string const & name);
    std::string getName () const;

    // Minimal RTTI implementation
    static std::string const & getTypeName ();

private:
    std::shared_ptr <function_impl> _impl;
}; // class function

} // namespace core
} // namespace omni

#endif // include guard
