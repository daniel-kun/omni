#ifndef OMNI_TAKE2_LITERAL_HPP
#define OMNI_TAKE2_LITERAL_HPP

#include <omni/take2/take2.hpp>
#include <memory>

namespace llvm {
    class Value;
}

namespace omni {
namespace take2 {
    class type;

    class OMNI_TAKE2_API literal {
    public:
        literal (std::shared_ptr <type> type);
        virtual ~ literal ();
        
        std::shared_ptr <type> getType ();
        const std::shared_ptr <type> getType () const;

        virtual llvm::Value * llvmValue () = 0;

    private:
        std::shared_ptr <type> _type;
    };

} // namespace take2
} // namespace omni

#endif // include guard
