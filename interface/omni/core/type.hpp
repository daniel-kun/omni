#ifndef OMNI_CORE_TYPE_HPP
#define OMNI_CORE_TYPE_HPP

#include <omni/core/core.hpp>
#include <omni/core/context_part.hpp>
#include <omni/core/type_class.hpp>

#include <boost/noncopyable.hpp>

namespace llvm {
    class Type;
}

namespace omni {
namespace core {

    class OMNI_CORE_API type : public context_part, public boost::noncopyable {
    public:
        type (context & context, type_class typeClass);
        virtual ~ type ();

        static std::shared_ptr <type> sharedBasicType (context & context, type_class typeClass);

        llvm::Type * llvmType ();

        type_class getTypeClass ();
        type_class const getTypeClass () const;

    private:
        type_class _typeClass;
    };

} // namespace core
} // namespace omni

#endif // include guard
