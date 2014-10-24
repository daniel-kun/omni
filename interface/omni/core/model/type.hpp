#ifndef OMNI_CORE_TYPE_HPP
#define OMNI_CORE_TYPE_HPP

#include <omni/core/core.hpp>
#include <omni/core/model/entity.hpp>
#include <omni/core/model/type_class.hpp>

#ifndef Q_MOC_RUN
#include <boost/noncopyable.hpp>
#endif

namespace llvm {
    class Type;
}

namespace omni {
namespace core {
namespace model {

    /**
    @class type type.hpp omni/core/model/type.hpp
    @brief A type defines the properties of types that can be used for variables, function-parameters, function-return-values, etc.

    <b>Important:</b> Always use type::sharedBasicType or context::sharedBasicType to get a type-object for any builtin-types.


    The type_class differentiates between a few basic built-in types and user-defined types (classes).
    (Currently, classes are not yet implemented for omni. Once they will be implemented, a new class class_type will be derived from
    type that implements various functionality and properties that classes offer.)

    A type is always strictly coupled with a context and, in contrast to most entities, can not exist without a context.
    Builtin-types are not defined in any module, hence getModule () always returns nullptr.
    Likely, builtin-classes do not have parents, hence getParent () always returns nullptr, too.
    **/
    class OMNI_CORE_API type : public entity, public boost::noncopyable {
    public:
        type (context & context, type_class typeClass, unsigned int indirectionLevel = 0);
        virtual ~ type ();

        std::string toString (bool fullyQualified = true);
        static std::string toString (type_class typeClass, bool fullyQualified = true);

        context * getContext () override;
        const context * getContext () const override;

        domain getDomain () const override;

        module * getModule () override;
        const module * getModule () const override;

        void setComponent (domain domain, std::string name, std::shared_ptr <entity> entity) override;

        type_class getTypeClass () const;

        unsigned int getIndirectionLevel () const;

        static std::shared_ptr <type> sharedBasicType(context & context, type_class typeClass, unsigned int indirectionLevel = 0);

        llvm::Type * llvmType ();

    private:
        context & _context;
        type_class _typeClass;
        unsigned int _indirectionLevel;
    };

} // namespace model
} // namespace core
} // namespace omni

#endif // include guard
