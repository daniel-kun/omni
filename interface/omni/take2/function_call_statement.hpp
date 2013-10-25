#ifndef OMNI_TAKE2_FUNCTION_CALL_STATEMENT_HPP
#define OMNI_TAKE2_FUNCTION_CALL_STATEMENT_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/statement.hpp>

namespace omni {
namespace take2 {

	/**
	A void function call is a statement, not an expression, because it does not have a result.
	**/
	class OMNI_TAKE2_API function_call_statement : public statement {
	public:
	};

} // namespace take2
} // namespace omni

#endif // include guard
