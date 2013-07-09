#ifndef OMNI_CORE_FUNCTION_HPP
#define OMNI_CORE_FUNCTION_HPP

#include <omni/core/core.hpp>
#include <omni/core/object.hpp>
#include <omni/core/instruction.hpp>
#include <string>

// forward declarations

namespace llvm {
class Function;
class BasicBlock;
}

// class definition

namespace omni {
namespace core {

class type;
class function_impl;

class OMNI_CORE_API function : public omni::core::object {
public:
	typedef std::list <instruction>::iterator instruction_it;

	function (type & type, std::string const & name);

	instruction_it instructionsBegin ();
	instruction_it instructionsEnd ();

	llvm::Function         * getLLVMFunction ();
	llvm::Function const   * getLLVMFunction () const;
	llvm::BasicBlock       * getLLVMBody ();
	llvm::BasicBlock const * getLLVMBody () const;

    void setName (std::string const & name);
	std::string getName () const;

	// Minimal RTTI implementation
	static std::string const & getTypeName ();

private:
	std::shared_ptr <function_impl> _impl;
}; // class function

} // namespace core
} // namespace omni

#endif // include guard
