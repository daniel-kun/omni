#ifndef OMNI_CORE_TYPE_HPP
#define OMNI_CORE_TYPE_HPP

#include <omni/core/core.hpp>
#include <omni/core/types.hpp>
#include <omni/core/function.hpp>
#include <list>
#include <string>
#include <memory>

// class definition

namespace omni {
namespace core {

class type_impl;
class module;

/**
The type class allows access to built-in and custom (class) types.
For built-in types such as types::Int, there is a corresponding llvm::Type
associated to this type. For custom types (user-defined classes), there is no llvm::Type
associated because they are not "visible" to llvm. Classes are just storage to llvm and in omni
they are a list of fields and methods. Methods are regular functions to llvm, omni takes care of
the this pointer and corresponding syntax and semantic.
types are the only place where functions can actually exist in.
**/
class OMNI_CORE_API type {
public:
	typedef std::list <function>::const_iterator function_const_it;
	typedef std::list <function>::iterator function_it;

	type (module & module, types t);
	type (module & module, std::string const & name);
	type (module & module, std::string const & uuid, std::string const & name);

	std::string const & getUuid () const;
	types getType () const;

	module const & getModule () const;
	module & getModule ();

	function & addFunction (std::string const & name);

	function_it		  functionsBegin ();
	function_const_it functionsBegin () const;
	function_it       functionsEnd ();
	function_const_it functionsEnd () const;

	static types getBasicTypeOf (types t);

	// Minimal RTTI
	static std::string const & getTypeName ();

private:
	std::shared_ptr <type_impl> _impl;
}; // class type 

} // namespace core
} // namespace omni

#endif // include guard
