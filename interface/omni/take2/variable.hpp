#ifndef OMNI_TAKE2_VARIABLE_HPP
#define OMNI_TAKE2_VARIABLE_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/context_part.hpp>
#include <string>

namespace omni {
namespace take2 {
    class context;
    class type;

	/**
	A local variable that was declared in a block and can be used in a variable_expression.
	**/
	class OMNI_TAKE2_API variable : public context_part {
	public:
		/**
		Initiailizes this variable as a new variable with the name `name' and a new id in the context `context'.
		**/
		variable (context & context, const type & type, const std::string & name);
		virtual ~ variable ();

		const type & getType () const;
	};

} // namespace take2
} // namespace omni

#endif // include guard
