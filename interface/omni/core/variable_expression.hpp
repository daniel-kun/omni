#ifndef OMNI_CORE_VARIABLE_EXPRESSION_HPP
#define OMNI_CORE_VARIABLE_EXPRESSION_HPP

#include <omni/core/core.hpp>
#include <omni/core/expression.hpp>

#include <memory>

namespace omni {
namespace core {
    class variable;

    /**
    A `variable expression' is any mention of a variable that is used to take that variable's value.
    E.g. in "int foo = x;", the "x" is a variable expression.
    **/
    class OMNI_CORE_API variable_expression : public expression {
    public:
        const std::shared_ptr <variable> getVariable () const;

    private:
        std::shared_ptr <variable> _variable;
    };

} // namespace core
} // namespace omni

#endif // include guard
