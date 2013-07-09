#ifndef OMNI_CORE_INSTRUCTION_HPP
#define OMNI_CORE_INSTRUCTION_HPP

#include <omni/core/core.hpp>
#include <string>
#include <memory>

// class definition

namespace omni {
namespace core {

class instruction_impl;

/**
instruction is the base class for everything that actually does something in your omni program.
Where type, function, etc. are metadata and define code structure, symbols and so on, instruction is the entry point
for the actual program logic.
**/
class OMNI_CORE_API instruction {
public:
			  instruction ();
	virtual ~ instruction ();

	static std::string const & getTypeName ();

private:
	std::shared_ptr <instruction_impl> _impl;
}; // class instruction

} // namespace core
} // namespace omni

#endif // include guard
