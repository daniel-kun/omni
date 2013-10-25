#ifndef OMNI_TAKE2_PARAMETER_HPP
#define OMNI_TAKE2_PARAMETER_HPP

#include <omni/take2/take2.hpp>
#include <omni/take2/context_part.hpp>

namespace omni {
namespace take2 {
    class type;

	/**
	Function parameter, @see function::getParameters ().
	**/
	class OMNI_TAKE2_API parameter : public context_part {
	public:
		const type & getType () const;
	};

} // namespace take2
} // namespace omni

#endif // include guard
