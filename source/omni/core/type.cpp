#include <omni/core/type.hpp>
#include <omni/core/module.hpp>
#include <omni/core/context.hpp>
#include <llvm/IR/DerivedTypes.h>
#include <sstream>
#include <stdexcept>

/**
Implementation details for type
**/
class omni::core::type_impl {
public:
    type_impl (module & module) :
        _module (module)
    {
    }

    module                     & _module;
    types                        _type;
    std::string                  _uuid;
    std::list <function>         _functions;
    std::shared_ptr <llvm::Type> _llvmType;
};

// Implementation of type

/**
Initialises this type object with the type t. t should not be typeClass. If you wish to create
a new class type, initialise this type with the constructor type(std::string const&)
**/
omni::core::type::type (omni::core::module & module, ::omni::core::types t) :
    _impl (new type_impl (module))
{
    _impl->_type = t;
	_impl->_uuid = module.getContext ().generateUuid ();
}

/**
Initialises this type object as a new class named `name' with a new uuid. The type will be typeClass.
**/
omni::core::type::type (omni::core::module & module, std::string const & name) :
    _impl (new type_impl (module))
{
    _impl->_uuid = context::generateUuid ();
    _impl->_type = types::Class;
}

/**
Initialises this type object as a class named `name' with the uuid `uuid'. The type will be typeClass.
This is usually used when deserializing a module.
**/
omni::core::type::type (omni::core::module & module, std::string const & uuid, std::string const & name) :
    _impl (new type_impl (module))
{
    _impl->_uuid = uuid;
    _impl->_type = types::Class;
}

/**
Returns the uuid for this type.
**/
std::string const & omni::core::type::getUuid () const
{
    return _impl->_uuid;
}

/**
Returns the kind of type for this type object.
**/
omni::core::types omni::core::type::getType () const
{
    return _impl->_type;
}

/**
Returns the module this type resides in.
**/
omni::core::module const & omni::core::type::getModule () const
{
	return _impl->_module;
}

/**
Returns the module this type resides in.
**/
omni::core::module & omni::core::type::getModule ()
{
	return _impl->_module;
}

/**
Adds a new function named name to this type.
**/
omni::core::function & omni::core::type::addFunction (std::string const & name)
{
    _impl->_functions.push_back (function (* this, name));
    return _impl->_functions.back ();
}

/**
Returns a begin-iterator for the functions in this type.
**/
omni::core::type::FunctionIt omni::core::type::functionsBegin ()
{
    return _impl->_functions.begin ();
}

/**
Returns a begin-iterator for the functions in this type.
**/
omni::core::type::FunctionIt omni::core::type::functionsBegin () const
{
    return _impl->_functions.begin ();
}

/**
Returns an end-iterator for the functions in this type.
**/
omni::core::type::FunctionIt omni::core::type::functionsEnd ()
{
    return _impl->_functions.end ();
}

/**
Returns an end-iterator for the functions in this type.
**/
omni::core::type::FunctionIt omni::core::type::functionsEnd () const
{
    return _impl->_functions.end ();
}

/**
Returns the basic type for the type t. For example, the basic type for typeInt32 is typeInt
or the basic type of typeUnsignedInt64 is typeUnsignedInt.
For floating point and character types and classes the result will be the same as t.
**/
omni::core::types omni::core::type::getBasicTypeOf (omni::core::types t)
{
    switch (t) {
    case types::Class:
    case types::Void:
    case types::Int:
    case types::UnsignedInt:
    case types::Short:
    case types::UnsignedShort:
    case types::Float:
    case types::Double:
    case types::Char:
    case types::UnsignedChar:
    case types::UnicodeChar:
        return t;
    case types::Int8:
        return types::Int;
    case types::Int16:
        return types::Int;
    case types::Int32:
        return types::Int;
    case types::Int64:
        return types::Int;
    case types::UnsignedInt8:
        return types::UnsignedInt;
    case types::UnsignedInt16:
        return types::UnsignedInt;
    case types::UnsignedInt32:
        return types::UnsignedInt;
    case types::UnsignedInt64:
        return types::UnsignedInt;
    case types::Short8:
        return types::Short;
    case types::Short16:
        return types::Short;
    case types::UnsignedShort8:
        return types::UnsignedShort;
    case types::UnsignedShort16:
        return types::UnsignedShort;
    }
    std::stringstream str;
    str << "Unknown type " << static_cast <int> (t);
    throw std::runtime_error (str.str ());
}

std::string const & omni::core::type::getTypeName ()
{
    static std::string result ("type");
    return result;
}
