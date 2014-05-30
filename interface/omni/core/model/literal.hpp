#ifndef OMNI_CORE_LITERAL_HPP
#define OMNI_CORE_LITERAL_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/scope.hpp>

#include <memory>

namespace llvm {
    class Value;
}

namespace omni {
namespace core {
namespace model {
    class type;

    /**
    A literal is a compile-time static value that can be used as expressions.
    To access the value of a literal e.g. as a function parameter or in an assignment or similar,
    use literal_expression.
    The most simple type is the builtin_literal<>, which is used to access literals of built-in types.
    (It is not sure whether other kinds of literals will be supported.)
    **/
    class OMNI_CORE_API literal : public scope {
    public:
        literal (std::shared_ptr <type> type);
        virtual ~ literal ();
        
        std::shared_ptr <type> getType ();
        const std::shared_ptr <type> getType () const;

        virtual llvm::Value * llvmValue () = 0;

    private:
        std::shared_ptr <type> _type;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
