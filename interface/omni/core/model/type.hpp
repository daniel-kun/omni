#ifndef OMNI_CORE_TYPE_HPP
#define OMNI_CORE_TYPE_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/entity.hpp>
#include <omni/core/model/type_class.hpp>

#include <boost/noncopyable.hpp>

namespace llvm {
    class Type;
}

namespace omni {
namespace core {
namespace model {

    class OMNI_CORE_API type : public entity, public boost::noncopyable {
    public:
        type (context & context, type_class typeClass, unsigned int indirectionLevel = 0);
        virtual ~ type ();

        virtual context * getContext ();
        virtual const context * getContext () const;

        virtual module * getModule ();
        virtual const module * getModule () const;

        static std::shared_ptr <type> sharedBasicType (context & context, type_class typeClass, unsigned int indirectionLevel = 0);

        llvm::Type * llvmType ();

        type_class getTypeClass () const;

        unsigned int getIndirectionLevel () const;

    private:
        context & _context;
        type_class _typeClass;
        unsigned int _indirectionLevel;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
