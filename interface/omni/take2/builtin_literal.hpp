#ifndef OMNI_TAKE2_BUILTIN_LITERAL_HPP
#define OMNI_TAKE2_BUILTIN_LITERAL_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/literal.hpp>
#include <omni/take2/not_implemented_error.hpp>

#include <memory>

namespace omni {
namespace take2 {
    class context;

    template <typename T>
    class OMNI_TAKE2_API builtin_literal : public literal {
    public:
        builtin_literal (context & context, T value);
        
        virtual llvm::Value * llvmValue ();

    private:
        T _value;
    };
}
}


#endif
