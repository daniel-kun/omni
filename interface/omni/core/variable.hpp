#ifndef OMNI_CORE_VARIABLE_HPP
#define OMNI_CORE_VARIABLE_HPP

#include <omni/core/core.hpp>
#include <omni/core/context_part.hpp>

#include <string>

namespace omni {
namespace core {
    class context;
    class type;

    /**
    A local variable that was declared in a block and can be used in a variable_expression.
    **/
    class OMNI_CORE_API variable : public context_part {
    public:
        /**
        Initiailizes this variable as a new variable with the name `name' and a new id in the context `context'.
        **/
        variable (context & context, const type & type, const std::string & name);
        virtual ~ variable ();

        const type & getType () const;
    };

} // namespace core
} // namespace omni

#endif // include guard
