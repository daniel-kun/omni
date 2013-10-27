#ifndef OMNI_TAKE2_TYPE_HPP
#define OMNI_TAKE2_TYPE_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/context_part.hpp>
#include <omni/take2/type_class.hpp>

namespace llvm {
    class Type;
}

namespace omni {
namespace take2 {

	class OMNI_TAKE2_API type : public context_part {
	public:
		type (context & context, type_class typeClass);
		virtual ~ type ();

        llvm::Type * llvmType ();

        type_class getTypeClass ();
        type_class const getTypeClass () const;

    private:
        type_class _typeClass;
	};

} // namespace take2
} // namespace omni

#endif // include guard
