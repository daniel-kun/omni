#ifndef OMNI_TAKE2_VARIABLE_EXPRESSION_HPP
#define OMNI_TAKE2_VARIABLE_EXPRESSION_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/expression.hpp>
#include <memory>

namespace omni {
namespace take2 {
    class variable;

	/**
	A `variable expression' is any mention of a variable that is used to take that variable's value.
	E.g. in "int foo = x;", the "x" is a variable expression.
	**/
	class OMNI_TAKE2_API variable_expression : public expression {
	public:
		const std::shared_ptr <variable> getVariable () const;

	private:
		std::shared_ptr <variable> _variable;
	};

} // namespace take2
} // namespace omni

#endif // include guard
